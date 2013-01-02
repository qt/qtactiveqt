/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtGui module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qaxutils_p.h"

#include <QtWidgets/QWidget>
#include <QtGui/QPixmap>
#include <QtGui/QRegion>
#include <QtGui/QWindow>
#include <QtGui/QGuiApplication>
#include <qpa/qplatformnativeinterface.h>
#include <qpa/qplatformpixmap.h>
#include <QtGui/private/qpixmap_raster_p.h>
#include <QtCore/QScopedArrayPointer>
#include <QtCore/QRect>

#include <QtCore/QDebug>

QT_BEGIN_NAMESPACE

static inline QWindow *windowForWidget(QWidget *widget)
{
    if (QWindow *window = widget->windowHandle())
        return window;
    if (QWidget *nativeParent = widget->nativeParentWidget())
        return nativeParent->windowHandle();
    return 0;
}

HWND hwndForWidget(QWidget *widget)
{
    if (QWindow *window = windowForWidget(widget))
        return static_cast<HWND> (QGuiApplication::platformNativeInterface()->nativeResourceForWindow("handle", window));
    return 0;
}

// Code courtesy of the Windows platform plugin (see pixmaputils.cpp/h).
HBITMAP qaxPixmapToWinHBITMAP(const QPixmap &p, HBitmapFormat format)
{
    if (p.isNull())
        return 0;

    HBITMAP bitmap = 0;
    if (p.handle()->classId() != QPlatformPixmap::RasterClass) {
        QRasterPlatformPixmap *data = new QRasterPlatformPixmap(p.depth() == 1 ?
            QRasterPlatformPixmap::BitmapType : QRasterPlatformPixmap::PixmapType);
        data->fromImage(p.toImage(), Qt::AutoColor);
        return qaxPixmapToWinHBITMAP(QPixmap(data), format);
    }

    QRasterPlatformPixmap *d = static_cast<QRasterPlatformPixmap*>(p.handle());
    const QImage *rasterImage = d->buffer();
    const int w = rasterImage->width();
    const int h = rasterImage->height();

    HDC display_dc = GetDC(0);

    // Define the header
    BITMAPINFO bmi;
    memset(&bmi, 0, sizeof(bmi));
    bmi.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth       = w;
    bmi.bmiHeader.biHeight      = -h;
    bmi.bmiHeader.biPlanes      = 1;
    bmi.bmiHeader.biBitCount    = 32;
    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biSizeImage   = w * h * 4;

    // Create the pixmap
    uchar *pixels = 0;
    bitmap = CreateDIBSection(display_dc, &bmi, DIB_RGB_COLORS, (void **) &pixels, 0, 0);
    ReleaseDC(0, display_dc);
    if (!bitmap) {
        qErrnoWarning("%s, failed to create dibsection", __FUNCTION__);
        return 0;
    }
    if (!pixels) {
        qErrnoWarning("%s, did not allocate pixel data", __FUNCTION__);
        return 0;
    }

    // Copy over the data
    QImage::Format imageFormat = QImage::Format_ARGB32;
    if (format == HBitmapAlpha)
        imageFormat = QImage::Format_RGB32;
    else if (format == HBitmapPremultipliedAlpha)
        imageFormat = QImage::Format_ARGB32_Premultiplied;
    const QImage image = rasterImage->convertToFormat(imageFormat);
    const int bytes_per_line = w * 4;
    for (int y=0; y < h; ++y)
        memcpy(pixels + y * bytes_per_line, image.scanLine(y), bytes_per_line);

    return bitmap;
}

QPixmap qaxPixmapFromWinHBITMAP(HBITMAP bitmap, HBitmapFormat format)
{
    // Verify size
    BITMAP bitmap_info;
    memset(&bitmap_info, 0, sizeof(BITMAP));

    const int res = GetObject(bitmap, sizeof(BITMAP), &bitmap_info);
    if (!res) {
        qErrnoWarning("QPixmap::fromWinHBITMAP(), failed to get bitmap info");
        return QPixmap();
    }
    const int w = bitmap_info.bmWidth;
    const int h = bitmap_info.bmHeight;

    BITMAPINFO bmi;
    memset(&bmi, 0, sizeof(bmi));
    bmi.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth       = w;
    bmi.bmiHeader.biHeight      = -h;
    bmi.bmiHeader.biPlanes      = 1;
    bmi.bmiHeader.biBitCount    = 32;
    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biSizeImage   = w * h * 4;

    // Get bitmap bits
    QScopedArrayPointer<uchar> data(new uchar[bmi.bmiHeader.biSizeImage]);
    HDC display_dc = GetDC(0);
    if (!GetDIBits(display_dc, bitmap, 0, h, data.data(), &bmi, DIB_RGB_COLORS)) {
        ReleaseDC(0, display_dc);
        qWarning("%s, failed to get bitmap bits", __FUNCTION__);
        return QPixmap();
    }

    QImage::Format imageFormat = QImage::Format_ARGB32_Premultiplied;
    uint mask = 0;
    if (format == HBitmapNoAlpha) {
        imageFormat = QImage::Format_RGB32;
        mask = 0xff000000;
    }

    // Create image and copy data into image.
    QImage image(w, h, imageFormat);
    if (image.isNull()) { // failed to alloc?
        ReleaseDC(0, display_dc);
        qWarning("%s, failed create image of %dx%d", __FUNCTION__, w, h);
        return QPixmap();
    }
    const int bytes_per_line = w * sizeof(QRgb);
    for (int y = 0; y < h; ++y) {
        QRgb *dest = (QRgb *) image.scanLine(y);
        const QRgb *src = (const QRgb *) (data.data() + y * bytes_per_line);
        for (int x = 0; x < w; ++x) {
            const uint pixel = src[x];
            if ((pixel & 0xff000000) == 0 && (pixel & 0x00ffffff) != 0)
                dest[x] = pixel | 0xff000000;
            else
                dest[x] = pixel | mask;
        }
    }
    ReleaseDC(0, display_dc);
    return QPixmap::fromImage(image);
}

// Code courtesy of QWindowsXPStyle
static void addRectToHrgn(HRGN &winRegion, const QRect &r)
{
    HRGN rgn = CreateRectRgn(r.left(), r.top(), r.x() + r.width(), r.y() + r.height());
    if (rgn) {
        HRGN dest = CreateRectRgn(0,0,0,0);
        int result = CombineRgn(dest, winRegion, rgn, RGN_OR);
        if (result) {
            DeleteObject(winRegion);
            winRegion = dest;
        }
        DeleteObject(rgn);
    }
}

HRGN qaxHrgnFromQRegion(const QRegion &region)
{
    HRGN hRegion = CreateRectRgn(0, 0, 0, 0);
    if (region.rectCount() == 1) {
        addRectToHrgn(hRegion, region.boundingRect());
        return hRegion;
    }
    foreach (const QRect &rect, region.rects())
        addRectToHrgn(hRegion, rect);
    return hRegion;
}

QT_END_NAMESPACE
