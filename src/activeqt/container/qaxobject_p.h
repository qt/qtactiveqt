/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
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
******************************************************************************/

#ifndef QAXOBJECT_P_H
#define QAXOBJECT_P_H

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

#include <QtAxContainer/qaxobject.h>
#include <private/qobject_p.h>
#include <private/qaxbase_p.h>

QT_BEGIN_NAMESPACE

class QAxObjectPrivate : public QObjectPrivate, public QAxBasePrivate
{
    Q_DECLARE_PUBLIC(QAxObject)
public:
    void clear();

    QObject* qObject() const override;
    const char *className() const override;
    const QMetaObject *fallbackMetaObject() const override;
    const QMetaObject *parentMetaObject() const override;

    void emitException(int code, const QString &source, const QString &desc,
                       const QString &help) override;
    void emitPropertyChanged(const QString &name) override;
    void emitSignal(const QString &name, int argc, void *argv) override;
};

QT_END_NAMESPACE

#endif // QAXOBJECT_P_H
