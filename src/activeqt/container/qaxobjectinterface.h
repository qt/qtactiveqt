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

#ifndef QAXOBJECTINTERFACE_H
#define QAXOBJECTINTERFACE_H

#include <QtCore/qglobal.h>

QT_BEGIN_NAMESPACE

class QString;

class QAxObjectInterface
{
public:
    virtual ~QAxObjectInterface();

    virtual ulong classContext() const = 0;
    virtual void setClassContext(ulong classContext) = 0;

    virtual QString control() const = 0;
    virtual void resetControl() = 0;
    virtual bool setControl(const QString &c) = 0;
};

QT_END_NAMESPACE

#endif // QAXOBJECTINTERFACE_H
