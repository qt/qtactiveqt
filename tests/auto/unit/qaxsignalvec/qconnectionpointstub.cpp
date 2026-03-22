// Copyright (C) 2026 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "qconnectionpointstub_p.h"

QConnectionPointStub::QConnectionPointStub(IID id)
    : m_id(id)
{
}

IFACEMETHODIMP QConnectionPointStub::GetConnectionInterface(IID *pIID)
{
    if (!pIID)
        return E_POINTER;

    *pIID = m_id;

    return S_OK;
}

IFACEMETHODIMP QConnectionPointStub::GetConnectionPointContainer(IConnectionPointContainer **ppCPC)
{
    return E_NOTIMPL;
}

IFACEMETHODIMP QConnectionPointStub::Advise(IUnknown *pUnkSink, DWORD *pdwCookie)
{
    return E_NOTIMPL;
}

IFACEMETHODIMP QConnectionPointStub::Unadvise(DWORD dwCookie)
{
    return E_NOTIMPL;
}

IFACEMETHODIMP QConnectionPointStub::EnumConnections(IEnumConnections **ppEnum)
{
    return E_NOTIMPL;
}
