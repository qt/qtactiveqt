// Copyright (C) 2026 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause
// Qt-Security score:significant reason:default


#ifndef IAXSERVERBASE_P_H
#define IAXSERVERBASE_P_H

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

#include <Unknwn.h>

#include <QtCore/qtconfigmacros.h>

QT_BEGIN_NAMESPACE

QT_WARNING_PUSH
QT_WARNING_DISABLE_GCC("-Wnon-virtual-dtor") // gcc complains about IAxServerBase inheriting IUnknown with non virtual destructor.

extern GUID IID_IAxServerBase;

class QObject;
class QString;

struct IAxServerBase : public IUnknown
{
    STDMETHOD_(IUnknown *, clientSite)() const = 0;
    STDMETHOD_(void, emitPropertyChanged)(const char *property) = 0;
    STDMETHOD_(bool, emitRequestPropertyChange)(const char *property) = 0;
    STDMETHOD_(QObject *, qObject)() const = 0;
    STDMETHOD_(void, reportError)(int code, const QString &src, const QString &desc, const QString &context) = 0;
};

QT_WARNING_POP

QT_END_NAMESPACE

#endif // IAXSERVERBASE_P_H
