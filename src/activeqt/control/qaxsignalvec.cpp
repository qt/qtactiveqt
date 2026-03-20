// Copyright (C) 2020 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause
// Qt-Security score:significant reason:default


#include "qaxsignalvec_p.h"

QT_BEGIN_NAMESPACE

QAxSignalVec::QAxSignalVec(const QAxServerBase::ConnectionPoints &points)
    : cpoints(points.values())
{
}

QAxSignalVec::QAxSignalVec(const QAxSignalVec &old)
    : cpoints(old.cpoints)
    , current(old.current)
{
}

IFACEMETHODIMP QAxSignalVec::Next(ULONG cConnections, IConnectionPoint **cpoint, ULONG *pcFetched)
{
    if (!cpoint)
        return E_POINTER;

    if (!pcFetched && cConnections > 1)
        return E_POINTER;

    const qsizetype count = cpoints.size();
    unsigned long i;
    for (i = 0; i < cConnections; i++) {
        if (current==count)
            break;
        auto &cp = cpoints.at(current);
        cpoint[i] = cp.Get();
        if (cp)
            cp->AddRef();
        ++current;
    }
    if (pcFetched)
        *pcFetched = i;
    return i == cConnections ? S_OK : S_FALSE;
}

IFACEMETHODIMP QAxSignalVec::Skip(ULONG cConnections)
{
    const qsizetype count = cpoints.size();
    while (cConnections) {
        if (current == count)
            return S_FALSE;
        ++current;
        --cConnections;
    }
    return S_OK;
}

IFACEMETHODIMP QAxSignalVec::Reset()
{
    current = 0;
    return S_OK;
}

IFACEMETHODIMP QAxSignalVec::Clone(IEnumConnectionPoints **ppEnum)
{
    if (!ppEnum)
        return E_POINTER;
    *ppEnum = new QAxSignalVec(*this);

    return S_OK;
}

QT_END_NAMESPACE
