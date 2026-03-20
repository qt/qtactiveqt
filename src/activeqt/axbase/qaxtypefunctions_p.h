// Copyright (C) 2015 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause
// Qt-Security score:significant reason:default


#ifndef QAXTYPEFUNCTIONS_P_H
#define QAXTYPEFUNCTIONS_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API. It exists purely as an
// implementation detail. This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtCore/qt_windows.h>

#include <QtGui/qcolor.h>
#include <QtGui/qfont.h>
#include <QtCore/qdatetime.h>
#include <QtCore/qvariant.h>

QT_BEGIN_NAMESPACE

#define HIMETRIC_PER_INCH   2540
#define MAP_PIX_TO_LOGHIM(x,ppli)   ((HIMETRIC_PER_INCH*(x) + ((ppli)>>1)) / (ppli))
#define MAP_LOGHIM_TO_PIX(x,ppli)   (((ppli)*(x) + HIMETRIC_PER_INCH/2) / HIMETRIC_PER_INCH)
#define QAX_NUM_PARAMS 8

static inline BSTR QStringToBSTR(const QString &str)
{
    return SysAllocStringLen(reinterpret_cast<const OLECHAR*>(str.unicode()), UINT(str.length()));
}

static inline uint QColorToOLEColor(const QColor &col)
{
    return qRgba(col.blue(), col.green(), col.red(), 0x00);
}

extern QColor OLEColorToQColor(uint col);
extern bool QVariantToVoidStar(const QVariant &var, void *data,
                               const QByteArray &typeName, int type = 0);
extern void clearVARIANT(VARIANT *var);

#define QAX_INPROC_SERVER  (0x51540001)
#define QAX_OUTPROC_SERVER (0x51540002)

QT_END_NAMESPACE

#endif // QAXTYPEFUNCTIONS_P_H
