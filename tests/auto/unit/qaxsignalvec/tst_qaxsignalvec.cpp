// Copyright (C) 2026 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QTest>

#ifdef Q_OS_WIN

#include <QtAxServer/private/qaxsignalvec_p.h>

#include "qconnectionpointstub_p.h"

#define QCOMPARE_POINT_INTERFACE(POINT, ID) \
    { \
        QCOMPARE_NE(POINT, nullptr); \
        IID id{}; \
        POINT->GetConnectionInterface(&id); \
        QCOMPARE(id, ID); \
    }

GUID IID_IInterfaceA = { 0xbd2ec165, 0xdfc9, 0x3219, { 0x8b, 0x9c, 0x60, 0xa5, 0x74, 0x78, 0xe9, 0x01 } };
GUID IID_IInterfaceB = { 0xbd2ec165, 0xdfc9, 0x3219, { 0x8b, 0x9c, 0x60, 0xa5, 0x74, 0x78, 0xe9, 0x02 } };
GUID IID_IInterfaceC = { 0xbd2ec165, 0xdfc9, 0x3219, { 0x8b, 0x9c, 0x60, 0xa5, 0x74, 0x78, 0xe9, 0x03 } };

class tst_QAxSignalVec : public QObject
{
    Q_OBJECT
private slots:
    void Next_returnsSFalse_whenCollectionIsEmpty();
    void Next_setsFetchedCountToZero_whenCollectionIsEmpty();
    void Next_returnsAllConnectionPoints_whenAllElementsAreRequested();
    void Next_returnsSFalse_whenNoMoreConnectionPointsAreAvailable();
    void Next_returnsSFalseAndPartialResult_whenRequestedCountExceedsRemainingPoints();
    void Next_returnsEPointer_whenOutputArrayIsNull();
    void Next_returnsEPointer_whenFetchedIsNullAndMoreThanOneElementIsRequested();
    void Next_allowsNullFetched_whenSingleElementIsRequested();
    void Next_advancesEnumerationPosition_betweenConsecutiveCalls();

    void Skip_advancesEnumerationPosition_whenRequestedCountIsWithinRemainingRange();
    void Skip_advancesEnumerationPosition_whenRequestedCountIsEqualToNumberOfElements();
    void Skip_doesNotAdvanceEnumerationPosition_whenSkippingPastEnd();

    void Reset_restoresEnumerationToBeginning_afterNextCall();
    void Reset_restoresEnumerationToBeginning_afterSkipCall();

    void Clone_preservesCurrentEnumerationState_afterPartialIteration();
    void Clone_preservesClonedEnumerator_afterOriginalAdvances();
    void Clone_preservesOriginalEnumerator_afterClonedAdvances();
};

void tst_QAxSignalVec::Next_returnsSFalse_whenCollectionIsEmpty()
{
    // Arrange
    ULONG fetched = 0;
    IConnectionPoint *points[3] = {};

    QAxSignalVec enumerator({});

    // Act
    const HRESULT result = enumerator.Next(3, points, &fetched);

    // Assert
    QCOMPARE(result, S_FALSE);
}

void tst_QAxSignalVec::Next_setsFetchedCountToZero_whenCollectionIsEmpty()
{
    // Arrange
    ULONG fetched = ULONG_MAX;
    IConnectionPoint *points[3] = {};

    QAxSignalVec enumerator({});

    // Act
    const HRESULT result = enumerator.Next(3, points, &fetched);

    // Assert
    QCOMPARE(fetched, 0);
}

void tst_QAxSignalVec::Next_returnsAllConnectionPoints_whenAllElementsAreRequested()
{
    // Arrange
    ULONG fetched = 0;
    IConnectionPoint *points[3] = {};

    QAxServerBase::ConnectionPoints idToPointMappings;
    idToPointMappings[IID_IInterfaceA] = makeComObject<QConnectionPointStub>(IID_IInterfaceA);
    idToPointMappings[IID_IInterfaceB] = makeComObject<QConnectionPointStub>(IID_IInterfaceB);
    idToPointMappings[IID_IInterfaceC] = makeComObject<QConnectionPointStub>(IID_IInterfaceC);
    QAxSignalVec enumerator(idToPointMappings);

    // Act
    const HRESULT result = enumerator.Next(3, points, &fetched);

    // Assert
    QCOMPARE(result, S_OK);
    QCOMPARE(fetched, 3);
    QCOMPARE_POINT_INTERFACE(points[0], IID_IInterfaceA);
    QCOMPARE_POINT_INTERFACE(points[1], IID_IInterfaceB);
    QCOMPARE_POINT_INTERFACE(points[2], IID_IInterfaceC);
}

void tst_QAxSignalVec::Next_returnsSFalse_whenNoMoreConnectionPointsAreAvailable()
{
    // Arrange
    ULONG fetched = 0;
    IConnectionPoint *points[3] = {};

    QAxServerBase::ConnectionPoints idToPointMappings;
    idToPointMappings[IID_IInterfaceA] = makeComObject<QConnectionPointStub>(IID_IInterfaceA);
    idToPointMappings[IID_IInterfaceB] = makeComObject<QConnectionPointStub>(IID_IInterfaceB);
    idToPointMappings[IID_IInterfaceC] = makeComObject<QConnectionPointStub>(IID_IInterfaceC);
    QAxSignalVec enumerator(idToPointMappings);
    enumerator.Next(3, points, &fetched);

    IConnectionPoint *point = nullptr;

    // Act
    const HRESULT result = enumerator.Next(1, &point, nullptr);

    // Assert
    QCOMPARE(result, S_FALSE);
    QCOMPARE(point, nullptr);
}

void tst_QAxSignalVec::Next_returnsSFalseAndPartialResult_whenRequestedCountExceedsRemainingPoints()
{
    // Arrange
    ULONG fetched = 0;
    IConnectionPoint *points[4] = {};

    QAxServerBase::ConnectionPoints idToPointMappings;
    idToPointMappings[IID_IInterfaceA] = makeComObject<QConnectionPointStub>(IID_IInterfaceA);
    idToPointMappings[IID_IInterfaceB] = makeComObject<QConnectionPointStub>(IID_IInterfaceB);
    idToPointMappings[IID_IInterfaceC] = makeComObject<QConnectionPointStub>(IID_IInterfaceC);
    QAxSignalVec enumerator(idToPointMappings);

    // Act
    const HRESULT result = enumerator.Next(4, points, &fetched);

    // Assert
    QCOMPARE(result, S_FALSE);
    QCOMPARE(fetched, 3);
    QCOMPARE_POINT_INTERFACE(points[0], IID_IInterfaceA);
    QCOMPARE_POINT_INTERFACE(points[1], IID_IInterfaceB);
    QCOMPARE_POINT_INTERFACE(points[2], IID_IInterfaceC);
    QCOMPARE(points[3], nullptr);
}

void tst_QAxSignalVec::Next_returnsEPointer_whenOutputArrayIsNull()
{
    // Arrange
    ULONG fetched = 0;

    QAxServerBase::ConnectionPoints idToPointMappings;
    idToPointMappings[IID_IInterfaceA] = makeComObject<QConnectionPointStub>(IID_IInterfaceA);
    idToPointMappings[IID_IInterfaceB] = makeComObject<QConnectionPointStub>(IID_IInterfaceB);
    idToPointMappings[IID_IInterfaceC] = makeComObject<QConnectionPointStub>(IID_IInterfaceC);
    QAxSignalVec enumerator(idToPointMappings);

    // Act
    const HRESULT result = enumerator.Next(3, nullptr, &fetched);

    // Assert
    QCOMPARE(result, E_POINTER);
    QCOMPARE(fetched, 0);
}

void tst_QAxSignalVec::Next_returnsEPointer_whenFetchedIsNullAndMoreThanOneElementIsRequested()
{
    // Arrange
    IConnectionPoint *points[3] = {};

    QAxServerBase::ConnectionPoints idToPointMappings;
    idToPointMappings[IID_IInterfaceA] = makeComObject<QConnectionPointStub>(IID_IInterfaceA);
    idToPointMappings[IID_IInterfaceB] = makeComObject<QConnectionPointStub>(IID_IInterfaceB);
    idToPointMappings[IID_IInterfaceC] = makeComObject<QConnectionPointStub>(IID_IInterfaceC);
    QAxSignalVec enumerator(idToPointMappings);

    // Act
    const HRESULT result = enumerator.Next(3, points, nullptr);

    // Assert
    QCOMPARE(result, E_POINTER);
    QCOMPARE(points[0], nullptr);
    QCOMPARE(points[1], nullptr);
    QCOMPARE(points[2], nullptr);
}

void tst_QAxSignalVec::Next_allowsNullFetched_whenSingleElementIsRequested()
{
    // Arrange
    IConnectionPoint *points[3] = {};

    QAxServerBase::ConnectionPoints idToPointMappings;
    idToPointMappings[IID_IInterfaceA] = makeComObject<QConnectionPointStub>(IID_IInterfaceA);
    idToPointMappings[IID_IInterfaceB] = makeComObject<QConnectionPointStub>(IID_IInterfaceB);
    idToPointMappings[IID_IInterfaceC] = makeComObject<QConnectionPointStub>(IID_IInterfaceC);
    QAxSignalVec enumerator(idToPointMappings);

    // Act
    const HRESULT result = enumerator.Next(1, points, nullptr);

    // Assert
    QCOMPARE(result, S_OK);
    QCOMPARE_POINT_INTERFACE(points[0], IID_IInterfaceA);
    QCOMPARE(points[1], nullptr);
    QCOMPARE(points[2], nullptr);
}

void tst_QAxSignalVec::Next_advancesEnumerationPosition_betweenConsecutiveCalls()
{
    // Arrange
    IConnectionPoint *point = nullptr;

    QAxServerBase::ConnectionPoints idToPointMappings;
    idToPointMappings[IID_IInterfaceA] = makeComObject<QConnectionPointStub>(IID_IInterfaceA);
    idToPointMappings[IID_IInterfaceB] = makeComObject<QConnectionPointStub>(IID_IInterfaceB);
    idToPointMappings[IID_IInterfaceC] = makeComObject<QConnectionPointStub>(IID_IInterfaceC);
    QAxSignalVec enumerator(idToPointMappings);
    enumerator.Next(1, &point, nullptr);

    point = nullptr;

    // Act
    const HRESULT result = enumerator.Next(1, &point, nullptr);

    // Assert
    QCOMPARE(result, S_OK);
    QCOMPARE_POINT_INTERFACE(point, IID_IInterfaceB);
}

void tst_QAxSignalVec::Skip_advancesEnumerationPosition_whenRequestedCountIsWithinRemainingRange()
{
    // Arrange
    QAxServerBase::ConnectionPoints idToPointMappings;
    idToPointMappings[IID_IInterfaceA] = makeComObject<QConnectionPointStub>(IID_IInterfaceA);
    idToPointMappings[IID_IInterfaceB] = makeComObject<QConnectionPointStub>(IID_IInterfaceB);
    idToPointMappings[IID_IInterfaceC] = makeComObject<QConnectionPointStub>(IID_IInterfaceC);
    QAxSignalVec enumerator(idToPointMappings);

    // Act
    const HRESULT result = enumerator.Skip(1);

    // Assert
    QCOMPARE(result, S_OK);

    IConnectionPoint *point = nullptr;
    enumerator.Next(1, &point, nullptr);
    QCOMPARE_POINT_INTERFACE(point, IID_IInterfaceB);
}

void tst_QAxSignalVec::Skip_advancesEnumerationPosition_whenRequestedCountIsEqualToNumberOfElements()
{
    // Arrange
    QAxServerBase::ConnectionPoints idToPointMappings;
    idToPointMappings[IID_IInterfaceA] = makeComObject<QConnectionPointStub>(IID_IInterfaceA);
    idToPointMappings[IID_IInterfaceB] = makeComObject<QConnectionPointStub>(IID_IInterfaceB);
    idToPointMappings[IID_IInterfaceC] = makeComObject<QConnectionPointStub>(IID_IInterfaceC);
    QAxSignalVec enumerator(idToPointMappings);

    // Act
    const HRESULT result = enumerator.Skip(3);

    // Assert
    QCOMPARE(result, S_OK);

    IConnectionPoint *point = nullptr;
    enumerator.Next(1, &point, nullptr);
    QCOMPARE(point, nullptr);
}

void tst_QAxSignalVec::Skip_doesNotAdvanceEnumerationPosition_whenSkippingPastEnd()
{
    // Arrange
    QAxServerBase::ConnectionPoints idToPointMappings;
    idToPointMappings[IID_IInterfaceA] = makeComObject<QConnectionPointStub>(IID_IInterfaceA);
    idToPointMappings[IID_IInterfaceB] = makeComObject<QConnectionPointStub>(IID_IInterfaceB);
    idToPointMappings[IID_IInterfaceC] = makeComObject<QConnectionPointStub>(IID_IInterfaceC);
    QAxSignalVec enumerator(idToPointMappings);

    // Act
    const HRESULT result = enumerator.Skip(4);

    // Assert
    QCOMPARE(result, S_FALSE);

    IConnectionPoint *point = nullptr;
    enumerator.Next(1, &point, nullptr);
    QCOMPARE_POINT_INTERFACE(point, IID_IInterfaceA);
}

void tst_QAxSignalVec::Reset_restoresEnumerationToBeginning_afterNextCall()
{
    // Arrange
    IConnectionPoint *point = nullptr;

    QAxServerBase::ConnectionPoints idToPointMappings;
    idToPointMappings[IID_IInterfaceA] = makeComObject<QConnectionPointStub>(IID_IInterfaceA);
    idToPointMappings[IID_IInterfaceB] = makeComObject<QConnectionPointStub>(IID_IInterfaceB);
    idToPointMappings[IID_IInterfaceC] = makeComObject<QConnectionPointStub>(IID_IInterfaceC);
    QAxSignalVec enumerator(idToPointMappings);
    enumerator.Next(1, &point, nullptr);

    // Act
    const HRESULT result = enumerator.Reset();

    // Assert
    QCOMPARE(result, S_OK);

    point = nullptr;
    enumerator.Next(1, &point, nullptr);
    QCOMPARE_POINT_INTERFACE(point, IID_IInterfaceA);
}

void tst_QAxSignalVec::Reset_restoresEnumerationToBeginning_afterSkipCall()
{
    // Arrange
    QAxServerBase::ConnectionPoints idToPointMappings;
    idToPointMappings[IID_IInterfaceA] = makeComObject<QConnectionPointStub>(IID_IInterfaceA);
    idToPointMappings[IID_IInterfaceB] = makeComObject<QConnectionPointStub>(IID_IInterfaceB);
    idToPointMappings[IID_IInterfaceC] = makeComObject<QConnectionPointStub>(IID_IInterfaceC);
    QAxSignalVec enumerator(idToPointMappings);
    enumerator.Skip(1);

    // Act
    const HRESULT result = enumerator.Reset();

    // Assert
    QCOMPARE(result, S_OK);

    IConnectionPoint *point = nullptr;
    enumerator.Next(1, &point, nullptr);
    QCOMPARE_POINT_INTERFACE(point, IID_IInterfaceA);
}

void tst_QAxSignalVec::Clone_preservesCurrentEnumerationState_afterPartialIteration()
{
    // Arrange
    IConnectionPoint *point = nullptr;

    QAxServerBase::ConnectionPoints idToPointMappings;
    idToPointMappings[IID_IInterfaceA] = makeComObject<QConnectionPointStub>(IID_IInterfaceA);
    idToPointMappings[IID_IInterfaceB] = makeComObject<QConnectionPointStub>(IID_IInterfaceB);
    idToPointMappings[IID_IInterfaceC] = makeComObject<QConnectionPointStub>(IID_IInterfaceC);
    QAxSignalVec enumerator(idToPointMappings);
    enumerator.Next(1, &point, nullptr);

    IEnumConnectionPoints *pointsCopy = nullptr;

    // Act
    const HRESULT result = enumerator.Clone(&pointsCopy);

    // Assert
    QCOMPARE(result, S_OK);
    QCOMPARE_NE(pointsCopy, nullptr);

    point = nullptr;
    pointsCopy->Next(1, &point, nullptr);
    QCOMPARE_POINT_INTERFACE(point, IID_IInterfaceB);
}

void tst_QAxSignalVec::Clone_preservesClonedEnumerator_afterOriginalAdvances()
{
    // Arrange
    IConnectionPoint *point = nullptr;

    QAxServerBase::ConnectionPoints idToPointMappings;
    idToPointMappings[IID_IInterfaceA] = makeComObject<QConnectionPointStub>(IID_IInterfaceA);
    idToPointMappings[IID_IInterfaceB] = makeComObject<QConnectionPointStub>(IID_IInterfaceB);
    idToPointMappings[IID_IInterfaceC] = makeComObject<QConnectionPointStub>(IID_IInterfaceC);
    QAxSignalVec enumerator(idToPointMappings);
    enumerator.Next(1, &point, nullptr);

    IEnumConnectionPoints *pointsCopy = nullptr;

    // Act
    const HRESULT result = enumerator.Clone(&pointsCopy);
    enumerator.Skip(1);

    // Assert
    QCOMPARE(result, S_OK);
    QCOMPARE_NE(pointsCopy, nullptr);

    point = nullptr;
    pointsCopy->Next(1, &point, nullptr);
    QCOMPARE_NE(point, nullptr);
    QCOMPARE_POINT_INTERFACE(point, IID_IInterfaceB);
}

void tst_QAxSignalVec::Clone_preservesOriginalEnumerator_afterClonedAdvances()
{
    // Arrange
    IConnectionPoint *point = nullptr;

    QAxServerBase::ConnectionPoints idToPointMappings;
    idToPointMappings[IID_IInterfaceA] = makeComObject<QConnectionPointStub>(IID_IInterfaceA);
    idToPointMappings[IID_IInterfaceB] = makeComObject<QConnectionPointStub>(IID_IInterfaceB);
    idToPointMappings[IID_IInterfaceC] = makeComObject<QConnectionPointStub>(IID_IInterfaceC);
    QAxSignalVec enumerator(idToPointMappings);
    enumerator.Next(1, &point, nullptr);

    IEnumConnectionPoints *pointsCopy = nullptr;

    // Act
    const HRESULT result = enumerator.Clone(&pointsCopy);
    if (pointsCopy)
        pointsCopy->Skip(1);

    // Assert
    QCOMPARE(result, S_OK);
    QCOMPARE_NE(pointsCopy, nullptr);

    point = nullptr;
    enumerator.Next(1, &point, nullptr);
    QCOMPARE_NE(point, nullptr);
    QCOMPARE_POINT_INTERFACE(point, IID_IInterfaceB);
}

QTEST_MAIN(tst_QAxSignalVec)
#include "tst_qaxsignalvec.moc"

#endif // Q_OS_WIN
