// Copyright (C) 2020 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause
// Qt-Security score:significant reason:default


#include "qaxsignalvec_p.h"

QT_BEGIN_NAMESPACE

QAxSignalVec::QAxSignalVec(const QAxServerBase::ConnectionPoints &points)
    : m_points(points.values())
{
}

QAxSignalVec::QAxSignalVec(const QAxSignalVec &old)
    : m_points(old.m_points), m_currentPointIndex(old.m_currentPointIndex)
{
}

IFACEMETHODIMP QAxSignalVec::Next(ULONG cConnections, LPCONNECTIONPOINT *ppCP, ULONG *pcFetched)
{
    if (!ppCP)
        return E_POINTER;
    if (!pcFetched && cConnections > 1)
        return E_POINTER;

    const qsizetype pointCount = m_points.size();

    ULONG pointIndex = 0;
    for (; pointIndex < cConnections; ++pointIndex) {
        if (m_currentPointIndex == pointCount)
            break;

        auto &point = m_points.at(m_currentPointIndex);
        ppCP[pointIndex] = point.Get();

        if (point)
            point->AddRef();

        ++m_currentPointIndex;
    }

    if (pcFetched)
        *pcFetched = pointIndex;

    return pointIndex == cConnections ? S_OK : S_FALSE;
}

IFACEMETHODIMP QAxSignalVec::Skip(ULONG cConnections)
{
    const qsizetype pointCount = m_points.size();

    while (cConnections > 0) {
        if (m_currentPointIndex == pointCount)
            return S_FALSE;

        ++m_currentPointIndex;
        --cConnections;
    }

    return S_OK;
}

IFACEMETHODIMP QAxSignalVec::Reset()
{
    m_currentPointIndex = 0;

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
