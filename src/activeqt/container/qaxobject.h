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

#ifndef QAXOBJECT_H
#define QAXOBJECT_H

#include <ActiveQt/qaxbase.h>

QT_BEGIN_NAMESPACE

class QAxObject : public QObject, public QAxBase
{
    friend class QAxEventSink;
    Q_OBJECT_FAKE
public:
    QObject* qObject() const override { return static_cast<QObject *>(const_cast<QAxObject *>(this)); }
    const char *className() const override;

    explicit QAxObject(QObject *parent = nullptr);
    explicit QAxObject(const QString &c, QObject *parent = nullptr);
    explicit QAxObject(IUnknown *iface, QObject *parent = nullptr);
    ~QAxObject() override;

    bool doVerb(const QString &verb);

protected:
    void connectNotify(const QMetaMethod &signal) override;
    const QMetaObject *fallbackMetaObject() const override;

private:
    const QMetaObject *parentMetaObject() const override;
};

template <> inline QAxObject *qobject_cast<QAxObject*>(const QObject *o)
{
    void *result = o ? const_cast<QObject *>(o)->qt_metacast("QAxObject") : nullptr;
    return reinterpret_cast<QAxObject*>(result);
}

template <> inline QAxObject *qobject_cast<QAxObject*>(QObject *o)
{
    void *result = o ? o->qt_metacast("QAxObject") : nullptr;
    return reinterpret_cast<QAxObject*>(result);
}

QT_END_NAMESPACE
Q_DECLARE_METATYPE(QAxObject*)

#endif // QAXOBJECT_H
