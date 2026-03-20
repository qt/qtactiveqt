// Copyright (C) 2026 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause
// Qt-Security score:significant reason:default


#ifndef QAXSERVERBASE_P_H
#define QAXSERVERBASE_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of other Qt classes.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <ocidl.h>

#include <QtCore/qtconfigmacros.h>

#include <QtCore/QHash>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QObject>
#include <QtCore/QPointer>
#include <QtCore/QSize>
#include <QtCore/QString>
#include <QtCore/QUuid>

#include <QtCore/private/qcomptr_p.h>

#include "iaxserverbase_p.h"

QT_BEGIN_NAMESPACE

class QAction;
class QAxAggregated;
class QMenu;
class QMenuBar;
class QStatusBar;
class QWidget;
struct QAxExceptInfo;

/*
    \class QAxServerBase
    \brief The QAxServerBase class is an ActiveX control hosting a QWidget.

    \internal
*/
class QAxServerBase : public QObject,
                      public IAxServerBase,
                      public IDispatch,
                      public IOleObject,
                      public IOleControl,
                      public IViewObject2,
                      public IOleInPlaceObject,
                      public IOleInPlaceActiveObject,
                      public IProvideClassInfo2,
                      public IConnectionPointContainer,
                      public IPersistStream,
                      public IPersistStreamInit,
                      public IPersistStorage,
                      public IPersistPropertyBag,
                      public IPersistFile,
                      public IDataObject
{
public:
    using ConnectionPoints = QMap<QUuid, ComPtr<IConnectionPoint>>;

    QAxServerBase(const QString &classname, IUnknown *outerUnknown);
    QAxServerBase(QObject *o);

    void init();

    ~QAxServerBase() override;

    // Window creation
    HWND create(HWND hWndParent, RECT &rcPos);
    HMENU createPopup(QMenu *popup, HMENU oldMenu = nullptr);
    void createMenu(QMenuBar *menuBar);
    void removeMenu();

    static LRESULT QT_WIN_CALLBACK ActiveXProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    // Object registration with OLE
    void registerActiveObject(IUnknown *object);
    void revokeActiveObject();

    // IUnknown
    IFACEMETHOD_(ULONG, AddRef)() override;
    IFACEMETHOD_(ULONG, Release)() override;
    IFACEMETHOD(QueryInterface)(REFIID riid, void **ppvObject) override;
    HRESULT InternalQueryInterface(REFIID iid, void **iface);

    // IAxServerBase
    IFACEMETHOD_(IUnknown *, ClientSite)() const override;

    IFACEMETHOD_(void, EmitPropertyChanged)(const char *property) override;
    IFACEMETHOD_(bool, EmitRequestPropertyChange)(const char *property) override;
    IFACEMETHOD_(QObject *, GetQObject)() const override;
    void ensureMetaData();
    bool isPropertyExposed(int index);

    IFACEMETHOD_(void, ReportError)(int code, const QString &src, const QString &desc,
                                    const QString &context) override;

    // IDispatch
    IFACEMETHOD(GetTypeInfoCount)(UINT *pctinfo) override;
    IFACEMETHOD(GetTypeInfo)(UINT iTInfo, LCID lcid, ITypeInfo **ppTInfo) override;
    IFACEMETHOD(GetIDsOfNames)(REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid,
                               DISPID *rgDispId) override;
    IFACEMETHOD(Invoke)(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags,
                        DISPPARAMS *pDispParams, VARIANT *pVarResult, EXCEPINFO *pExcepInfo,
                        UINT *puArgErr) override;

    // IProvideClassInfo
    IFACEMETHOD(GetClassInfo)(ITypeInfo **ppTI) override;

    // IProvideClassInfo2
    IFACEMETHOD(GetGUID)(DWORD dwGuidKind, GUID *pGUID) override;

    // IOleObject
    IFACEMETHOD(Advise)(IAdviseSink *pAdvSink, DWORD *pdwConnection) override;
    IFACEMETHOD(Close)(DWORD dwSaveOption) override;
    IFACEMETHOD(DoVerb)(LONG iVerb, LPMSG lpmsg, IOleClientSite *pActiveSite, LONG lindex,
                        HWND hwndParent, LPCRECT lprcPosRect) override;
    IFACEMETHOD(EnumAdvise)(IEnumSTATDATA **ppenumAdvise) override;
    IFACEMETHOD(EnumVerbs)(IEnumOLEVERB **ppEnumOleVerb) override;
    IFACEMETHOD(GetClientSite)(IOleClientSite **ppClientSite) override;
    IFACEMETHOD(GetClipboardData)(DWORD dwReserved, IDataObject **ppDataObject) override;
    IFACEMETHOD(GetExtent)(DWORD dwDrawAspect, SIZEL *psizel) override;
    IFACEMETHOD(GetMiscStatus)(DWORD dwAspect, DWORD *pdwStatus) override;
    IFACEMETHOD(GetMoniker)(DWORD dwAssign, DWORD dwWhichMoniker, IMoniker **ppmk) override;
    IFACEMETHOD(GetUserClassID)(CLSID *pClsid) override;
    IFACEMETHOD(GetUserType)(DWORD dwFormOfType, LPOLESTR *pszUserType) override;
    IFACEMETHOD(InitFromData)(IDataObject *pDataObject, BOOL fCreation, DWORD dwReserved) override;
    IFACEMETHOD(IsUpToDate)() override;
    IFACEMETHOD(SetClientSite)(IOleClientSite *pClientSite) override;
    IFACEMETHOD(SetColorScheme)(LOGPALETTE *pLogpal) override;
    IFACEMETHOD(SetExtent)(DWORD dwDrawAspect, SIZEL *psizel) override;
    IFACEMETHOD(SetHostNames)(LPCOLESTR szContainerApp, LPCOLESTR szContainerObj) override;
    IFACEMETHOD(SetMoniker)(DWORD dwWhichMoniker, IMoniker *pmk) override;
    IFACEMETHOD(Unadvise)(DWORD dwConnection) override;
    IFACEMETHOD(Update)() override;

    // IViewObject
    IFACEMETHOD(Draw)(DWORD dwDrawAspect, LONG lindex, void *pvAspect, DVTARGETDEVICE *ptd,
                      HDC hdcTargetDev, HDC hdcDraw, LPCRECTL lprcBounds, LPCRECTL lprcWBounds,
                      BOOL(STDMETHODCALLTYPE *pfnContinue)(ULONG_PTR),
                      ULONG_PTR dwContinue) override;
    IFACEMETHOD(GetColorSet)(DWORD dwDrawAspect, LONG lindex, void *pvAspect, DVTARGETDEVICE *ptd,
                             HDC hicTargetDev, LOGPALETTE **ppColorSet) override;
    IFACEMETHOD(Freeze)(DWORD dwDrawAspect, LONG lindex, void *pvAspect, DWORD *pdwFreeze) override;
    IFACEMETHOD(Unfreeze)(DWORD dwFreeze) override;
    IFACEMETHOD(SetAdvise)(DWORD aspects, DWORD advf, IAdviseSink *pAdvSink) override;
    IFACEMETHOD(GetAdvise)(DWORD *pAspects, DWORD *pAdvf, IAdviseSink **ppAdvSink) override;

    // IViewObject2
    IFACEMETHOD(GetExtent)(DWORD dwDrawAspect, LONG lindex, DVTARGETDEVICE *ptd,
                           LPSIZEL lpsizel) override;

    // IOleControl
    IFACEMETHOD(FreezeEvents)(BOOL bFreeze) override;
    IFACEMETHOD(GetControlInfo)(CONTROLINFO *pCI) override;
    IFACEMETHOD(OnAmbientPropertyChange)(DISPID dispID) override;
    IFACEMETHOD(OnMnemonic)(MSG *pMsg) override;

    // IOleWindow
    IFACEMETHOD(GetWindow)(HWND *phwnd) override;
    IFACEMETHOD(ContextSensitiveHelp)(BOOL fEnterMode) override;

    // IOleInPlaceObject
    IFACEMETHOD(InPlaceDeactivate)() override;
    IFACEMETHOD(UIDeactivate)() override;
    IFACEMETHOD(SetObjectRects)(LPCRECT lprcPosRect, LPCRECT lprcClipRect) override;
    IFACEMETHOD(ReactivateAndUndo)() override;

    // IOleInPlaceActiveObject
    IFACEMETHOD(TranslateAccelerator)(LPMSG lpmsg) override;
    IFACEMETHOD(OnFrameWindowActivate)(BOOL fActivate) override;
    IFACEMETHOD(OnDocWindowActivate)(BOOL fActivate) override;
    IFACEMETHOD(ResizeBorder)(LPCRECT prcBorder, IOleInPlaceUIWindow *pUIWindow,
                              BOOL fFrameWindow) override;
    IFACEMETHOD(EnableModeless)(BOOL fEnable) override;

    // IConnectionPointContainer
    IFACEMETHOD(EnumConnectionPoints)(IEnumConnectionPoints **ppEnum) override;
    IFACEMETHOD(FindConnectionPoint)(REFIID riid, IConnectionPoint **ppCP) override;

    // IPersist
    IFACEMETHOD(GetClassID)(CLSID *pClassID) override;

    // IPersistStreamInit
    IFACEMETHOD(InitNew)() override;
    IFACEMETHOD(IsDirty)() override;
    IFACEMETHOD(Load)(LPSTREAM pStm) override;
    IFACEMETHOD(Save)(LPSTREAM pStm, BOOL fClearDirty) override;
    IFACEMETHOD(GetSizeMax)(ULARGE_INTEGER *pCbSize) override;

    // IPersistPropertyBag
    IFACEMETHOD(Load)(IPropertyBag *pPropBag, IErrorLog *pErrorLog) override;
    IFACEMETHOD(Save)(IPropertyBag *pPropBag, BOOL fClearDirty, BOOL fSaveAllProperties) override;

    // IPersistStorage
    IFACEMETHOD(InitNew)(IStorage *pStg) override;
    IFACEMETHOD(Load)(IStorage *pStg) override;
    IFACEMETHOD(Save)(IStorage *pStgSave, BOOL fSameAsLoad) override;
    IFACEMETHOD(SaveCompleted)(IStorage *pStgNew) override;
    IFACEMETHOD(HandsOffStorage)() override;

    // IPersistFile
    IFACEMETHOD(SaveCompleted)(LPCOLESTR pszFileName) override;
    IFACEMETHOD(GetCurFile)(LPOLESTR *ppszFileName) override;
    IFACEMETHOD(Load)(LPCOLESTR pszFileName, DWORD dwMode) override;
    IFACEMETHOD(Save)(LPCOLESTR pszFileName, BOOL fRemember) override;

    // IDataObject
    IFACEMETHOD(GetData)(FORMATETC *pformatetcIn, STGMEDIUM *pmedium) override;
    IFACEMETHOD(GetDataHere)(FORMATETC *pformatetc, STGMEDIUM *pmedium) override;
    IFACEMETHOD(QueryGetData)(FORMATETC *pformatetc) override;
    IFACEMETHOD(GetCanonicalFormatEtc)(FORMATETC *pformatectIn, FORMATETC *pformatetcOut) override;
    IFACEMETHOD(SetData)(FORMATETC *pformatetc, STGMEDIUM *pmedium, BOOL fRelease) override;
    IFACEMETHOD(EnumFormatEtc)(DWORD dwDirection, IEnumFORMATETC **ppenumFormatEtc) override;
    IFACEMETHOD(DAdvise)(FORMATETC *pformatetc, DWORD advf, IAdviseSink *pAdvSink,
                         DWORD *pdwConnection) override;
    IFACEMETHOD(DUnadvise)(DWORD dwConnection) override;
    IFACEMETHOD(EnumDAdvise)(IEnumSTATDATA **ppenumAdvise) override;

    // QObject
    int qt_metacall(QMetaObject::Call, int index, void **argv) override;

    bool eventFilter(QObject *o, QEvent *e) override;

    RECT rcPosRect() const;

private:
    void update();
    void resize(const QSize &newSize);
    void updateGeometry();
    void updateMask();
    bool internalCreate();
    void internalBind();
    void internalConnect();
    HRESULT internalActivate();

    friend class QAxBindable;
    friend class QAxPropertyPage;
    QAxAggregated *aggregatedObject = nullptr;
    ConnectionPoints points;

    union {
        QWidget *widget;
        QObject *object;
    } qt;
    QPointer<QObject> theObject;
    unsigned isWidget        : 1;
    unsigned ownObject       : 1;
    unsigned initNewCalled   : 1;
    unsigned dirtyflag       : 1;
    unsigned hasStockEvents  : 1;
    unsigned stayTopLevel    : 1;
    unsigned isInPlaceActive : 1;
    unsigned isUIActive      : 1;
    unsigned wasUIActive     : 1;
    unsigned inDesignMode    : 1;
    unsigned canTakeFocus    : 1;
    short freezeEvents = 0;

    HWND m_hWnd = nullptr;

    HMENU hmenuShared = nullptr;
    HOLEMENU holemenu = nullptr;
    HWND hwndMenuOwner = nullptr;
    QMap<HMENU, QMenu *> menuMap;
    QMap<UINT, QAction *> actionMap;
    QPointer<QMenuBar> menuBar;
    QPointer<QStatusBar> statusBar;
    QPointer<QMenu> currentPopup;
    std::unique_ptr<QAxExceptInfo> exception;

    CRITICAL_SECTION refCountSection;
    CRITICAL_SECTION createWindowSection;

    LONG ref = 0;
    unsigned long ole_ref = 0;

    QString class_name;
    QString currentFileName;

    QHash<long, int> indexCache;
    QHash<int, DISPID> signalCache;

    IUnknown *m_outerUnknown = nullptr;
    ComPtr<IAdviseSink> m_spAdviseSink;
    QList<STATDATA> adviseSinks;
    ComPtr<IOleClientSite> m_spClientSite;
    ComPtr<IOleInPlaceSite> m_spInPlaceSite;
    ComPtr<IOleInPlaceSiteWindowless> m_spInPlaceSiteWindowless;
    ComPtr<IOleInPlaceFrame> m_spInPlaceFrame;
    ComPtr<ITypeInfo> m_spTypeInfo;
    ComPtr<IStorage> m_spStorage;
    QSize m_currentExtent; // device independent pixels.

    DWORD m_nextAdviseConnection = 0;
};

QT_END_NAMESPACE

#endif // QAXSERVERBASE_P_H
