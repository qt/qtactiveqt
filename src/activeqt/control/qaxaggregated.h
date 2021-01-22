/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the ActiveQt framework of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
****************************************************************************/

#ifndef QAXAGGREGATED_H
#define QAXAGGREGATED_H

#include <QtCore/qobject.h>

struct IUnknown;

QT_BEGIN_NAMESPACE

class QWidget;

class QUuid;

class QAxAggregated
{
    friend class QAxServerBase;
    friend class QAxClientSite;
    Q_DISABLE_COPY_MOVE(QAxAggregated)
public:
    virtual long queryInterface(const QUuid &iid, void **iface) = 0;

protected:
    QAxAggregated() = default;
    virtual ~QAxAggregated() = default;

    inline IUnknown *controllingUnknown() const
    { return controlling_unknown; }
    QWidget *widget() const;
    inline QObject *object() const { return the_object; }

private:
    IUnknown *controlling_unknown = nullptr;
    QObject *the_object = nullptr;
};

#define QAXAGG_IUNKNOWN \
    HRESULT WINAPI QueryInterface(REFIID iid, LPVOID *iface) override \
        { return controllingUnknown()->QueryInterface(iid, iface); } \
    ULONG WINAPI AddRef() override { return controllingUnknown()->AddRef(); } \
    ULONG WINAPI Release() override { return controllingUnknown()->Release(); } \

QT_END_NAMESPACE

#endif // QAXAGGREGATED_H
