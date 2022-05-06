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

#ifndef QAXTYPES_H
#define QAXTYPES_H

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

#include <QtCore/qbytearray.h>
#include <QtCore/qvariant.h>

#include <QtCore/qt_windows.h>

QT_BEGIN_NAMESPACE

#ifdef QAX_SERVER
#   define QVariantToVARIANTFunc QVariantToVARIANT_server
#   define VARIANTToQVariantFunc VARIANTToQVariant_server
#else
#   define QVariantToVARIANTFunc QVariantToVARIANT_container
#   define VARIANTToQVariantFunc VARIANTToQVariant_container
#endif

extern bool QVariantToVARIANTFunc(const QVariant &var, VARIANT &arg, const QByteArray &typeName = QByteArray(), bool out = false);
extern QVariant VARIANTToQVariantFunc(const VARIANT &arg, const QByteArray &typeName,
                                      int type = 0);

inline bool QVariantToVARIANT(const QVariant &var, VARIANT &arg, const QByteArray &typeName = QByteArray(), bool out = false)
{
    return QVariantToVARIANTFunc(var, arg, typeName, out);
}

inline QVariant VARIANTToQVariant(const VARIANT &arg, const QByteArray &typeName,
                                  int type = 0)
{
    return VARIANTToQVariantFunc(arg, typeName, type);
}

#undef QVariantToVARIANTFunc
#undef VARIANTToQVariantFunc

QT_END_NAMESPACE

#endif // QAXTYPES_H
