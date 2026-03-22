// Copyright (C) 2026 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only


#ifndef QCONNECTIONPOINTSTUB_P_H
#define QCONNECTIONPOINTSTUB_P_H

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

#include <QtCore/private/qcomobject_p.h>

class QConnectionPointStub : public QComObject<IConnectionPoint>
{
public:
    QConnectionPointStub(IID id);

    // IConnectionPoint
    IFACEMETHOD(GetConnectionInterface)(IID *pIID) override;
    IFACEMETHOD(GetConnectionPointContainer)(IConnectionPointContainer **ppCPC) override;
    IFACEMETHOD(Advise)(IUnknown *pUnkSink, DWORD *pdwCookie) override;
    IFACEMETHOD(Unadvise)(DWORD dwCookie) override;
    IFACEMETHOD(EnumConnections)(IEnumConnections **ppEnum) override;

private:
    IID m_id;
};

#endif // QCONNECTIONPOINTSTUB_P_H
