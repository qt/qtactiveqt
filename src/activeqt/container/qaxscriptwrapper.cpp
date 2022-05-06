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

#include "qaxobject.h"

#include <QtAxServer/qaxfactory.h>

#include <qt_windows.h>

QT_BEGIN_NAMESPACE

QAxBase *qax_create_object_wrapper(QObject *object)
{
    IDispatch *dispatch = nullptr;
    QAxObject *wrapper = nullptr;
    qAxFactory()->createObjectWrapper(object, &dispatch);
    if (dispatch) {
        wrapper = new QAxObject(dispatch, object);
        wrapper->setObjectName(object->objectName());
        dispatch->Release();
    }
    return wrapper;
}

QT_END_NAMESPACE
