// Copyright (C) 2026 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause
// Qt-Security score:significant reason:default


#ifndef QAXSIGNALVEC_P_H
#define QAXSIGNALVEC_P_H

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

#include <ocidl.h>

#include <QtCore/qtconfigmacros.h>
#include <QtCore/private/qcomobject_p.h>
#include <QtCore/private/qcomptr_p.h>

#include "qaxserverbase_p.h"

QT_BEGIN_NAMESPACE

/*
    Helper class to enumerate all supported event interfaces.
*/
class QAxSignalVec : public QComObject<IEnumConnectionPoints>
{
public:
    QAxSignalVec &operator=(const QAxSignalVec &) = delete;
    QAxSignalVec &operator=(QAxSignalVec &&) = delete;
    QAxSignalVec(QAxSignalVec &&) = delete;

    QAxSignalVec(const QAxServerBase::ConnectionPoints &points);
    QAxSignalVec(const QAxSignalVec &old);

    // IEnumConnectionPoints
    IFACEMETHOD(Next)(ULONG cConnections, LPCONNECTIONPOINT *ppCP, ULONG *pcFetched) override;
    IFACEMETHOD(Skip)(ULONG cConnections) override;
    IFACEMETHOD(Reset)() override;
    IFACEMETHOD(Clone)(IEnumConnectionPoints **ppEnum) override;

private:
    QList<ComPtr<IConnectionPoint>> m_points;
    int m_currentPointIndex{ 0 };
};

QT_END_NAMESPACE

#endif // QAXSIGNALVEC_P_H
