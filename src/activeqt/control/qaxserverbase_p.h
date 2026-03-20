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
    unsigned long WINAPI AddRef() override;
    unsigned long WINAPI Release() override;
    HRESULT WINAPI QueryInterface(REFIID iid, void **iface) override;
    HRESULT InternalQueryInterface(REFIID iid, void **iface);

    // IAxServerBase
    IUnknown *ClientSite() const override;

    void EmitPropertyChanged(const char *) override;
    bool EmitRequestPropertyChange(const char *) override;
    QObject *GetQObject() const override;
    void ensureMetaData();
    bool isPropertyExposed(int index);

    void ReportError(int code, const QString &src, const QString &desc,
                     const QString &context) override;

    // IDispatch
    STDMETHOD(GetTypeInfoCount)(UINT *pctinfo) override;
    STDMETHOD(GetTypeInfo)(UINT itinfo, LCID lcid, ITypeInfo **pptinfo) override;
    STDMETHOD(GetIDsOfNames)(REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid,
                             DISPID *rgdispid) override;
    STDMETHOD(Invoke)(DISPID dispidMember, REFIID riid, LCID lcid, WORD wFlags,
                      DISPPARAMS *pdispparams, VARIANT *pvarResult, EXCEPINFO *pexcepinfo,
                      UINT *puArgErr) override;

    // IProvideClassInfo
    STDMETHOD(GetClassInfo)(ITypeInfo **pptinfo) override;

    // IProvideClassInfo2
    STDMETHOD(GetGUID)(DWORD dwGuidKind, GUID *pGUID) override;

    // IOleObject
    STDMETHOD(Advise)(IAdviseSink *pAdvSink, DWORD *pdwConnection) override;
    STDMETHOD(Close)(DWORD dwSaveOption) override;
    STDMETHOD(DoVerb)(LONG iVerb, LPMSG lpmsg, IOleClientSite *pActiveSite, LONG lindex,
                      HWND hwndParent, LPCRECT lprcPosRect) override;
    STDMETHOD(EnumAdvise)(IEnumSTATDATA **ppenumAdvise) override;
    STDMETHOD(EnumVerbs)(IEnumOLEVERB **ppEnumOleVerb) override;
    STDMETHOD(GetClientSite)(IOleClientSite **ppClientSite) override;
    STDMETHOD(GetClipboardData)(DWORD dwReserved, IDataObject **ppDataObject) override;
    STDMETHOD(GetExtent)(DWORD dwDrawAspect, SIZEL *psizel) override;
    STDMETHOD(GetMiscStatus)(DWORD dwAspect, DWORD *pdwStatus) override;
    STDMETHOD(GetMoniker)(DWORD dwAssign, DWORD dwWhichMoniker, IMoniker **ppmk) override;
    STDMETHOD(GetUserClassID)(CLSID *pClsid) override;
    STDMETHOD(GetUserType)(DWORD dwFormOfType, LPOLESTR *pszUserType) override;
    STDMETHOD(InitFromData)(IDataObject *pDataObject, BOOL fCreation, DWORD dwReserved) override;
    STDMETHOD(IsUpToDate)() override;
    STDMETHOD(SetClientSite)(IOleClientSite *pClientSite) override;
    STDMETHOD(SetColorScheme)(LOGPALETTE *pLogPal) override;
    STDMETHOD(SetExtent)(DWORD dwDrawAspect, SIZEL *psizel) override;
    STDMETHOD(SetHostNames)(LPCOLESTR szContainerApp, LPCOLESTR szContainerObj) override;
    STDMETHOD(SetMoniker)(DWORD dwWhichMoniker, IMoniker *ppmk) override;
    STDMETHOD(Unadvise)(DWORD dwConnection) override;
    STDMETHOD(Update)() override;

    // IViewObject
    STDMETHOD(Draw)(DWORD dwAspect, LONG lIndex, void *pvAspect, DVTARGETDEVICE *ptd,
                    HDC hicTargetDevice, HDC hdcDraw, LPCRECTL lprcBounds, LPCRECTL lprcWBounds,
                    BOOL(__stdcall *pfnContinue)(ULONG_PTR), ULONG_PTR dwContinue) override;
    STDMETHOD(GetColorSet)(DWORD dwDrawAspect, LONG lindex, void *pvAspect, DVTARGETDEVICE *ptd,
                           HDC hicTargetDev, LOGPALETTE **ppColorSet) override;
    STDMETHOD(Freeze)(DWORD dwAspect, LONG lindex, void *pvAspect, DWORD *pdwFreeze) override;
    STDMETHOD(Unfreeze)(DWORD dwFreeze) override;
    STDMETHOD(SetAdvise)(DWORD aspects, DWORD advf, IAdviseSink *pAdvSink) override;
    STDMETHOD(GetAdvise)(DWORD *aspects, DWORD *advf, IAdviseSink **pAdvSink) override;

    // IViewObject2
    STDMETHOD(GetExtent)(DWORD dwAspect, LONG lindex, DVTARGETDEVICE *ptd,
                         LPSIZEL lpsizel) override;

    // IOleControl
    STDMETHOD(FreezeEvents)(BOOL) override;
    STDMETHOD(GetControlInfo)(LPCONTROLINFO) override;
    STDMETHOD(OnAmbientPropertyChange)(DISPID) override;
    STDMETHOD(OnMnemonic)(LPMSG) override;

    // IOleWindow
    STDMETHOD(GetWindow)(HWND *pHwnd) override;
    STDMETHOD(ContextSensitiveHelp)(BOOL fEnterMode) override;

    // IOleInPlaceObject
    STDMETHOD(InPlaceDeactivate)() override;
    STDMETHOD(UIDeactivate)() override;
    STDMETHOD(SetObjectRects)(LPCRECT lprcPosRect, LPCRECT lprcClipRect) override;
    STDMETHOD(ReactivateAndUndo)() override;

    // IOleInPlaceActiveObject
    STDMETHOD(TranslateAccelerator)(MSG *pMsg) override;
    STDMETHOD(OnFrameWindowActivate)(BOOL) override;
    STDMETHOD(OnDocWindowActivate)(BOOL fActivate) override;
    STDMETHOD(ResizeBorder)(LPCRECT prcBorder, IOleInPlaceUIWindow *pUIWindow,
                            BOOL fFrameWindow) override;
    STDMETHOD(EnableModeless)(BOOL) override;

    // IConnectionPointContainer
    STDMETHOD(EnumConnectionPoints)(IEnumConnectionPoints **) override;
    STDMETHOD(FindConnectionPoint)(REFIID, IConnectionPoint **) override;

    // IPersist
    STDMETHOD(GetClassID)(GUID *clsid) override;

    // IPersistStreamInit
    STDMETHOD(InitNew)(VOID) override;
    STDMETHOD(IsDirty)() override;
    STDMETHOD(Load)(IStream *pStm) override;
    STDMETHOD(Save)(IStream *pStm, BOOL fClearDirty) override;
    STDMETHOD(GetSizeMax)(ULARGE_INTEGER *pcbSize) override;

    // IPersistPropertyBag
    STDMETHOD(Load)(IPropertyBag *, IErrorLog *) override;
    STDMETHOD(Save)(IPropertyBag *, BOOL, BOOL) override;

    // IPersistStorage
    STDMETHOD(InitNew)(IStorage *pStg) override;
    STDMETHOD(Load)(IStorage *pStg) override;
    STDMETHOD(Save)(IStorage *pStg, BOOL fSameAsLoad) override;
    STDMETHOD(SaveCompleted)(IStorage *pStgNew) override;
    STDMETHOD(HandsOffStorage)() override;

    // IPersistFile
    STDMETHOD(SaveCompleted)(LPCOLESTR fileName) override;
    STDMETHOD(GetCurFile)(LPOLESTR *currentFile) override;
    STDMETHOD(Load)(LPCOLESTR fileName, DWORD mode) override;
    STDMETHOD(Save)(LPCOLESTR fileName, BOOL fRemember) override;

    // IDataObject
    STDMETHOD(GetData)(FORMATETC *pformatetcIn, STGMEDIUM *pmedium) override;
    STDMETHOD(GetDataHere)(FORMATETC * /* pformatetc */, STGMEDIUM * /* pmedium */) override;
    STDMETHOD(QueryGetData)(FORMATETC * /* pformatetc */) override;
    STDMETHOD(GetCanonicalFormatEtc)(FORMATETC * /* pformatectIn */,
                                     FORMATETC * /* pformatetcOut */) override;
    STDMETHOD(SetData)(FORMATETC * /* pformatetc */, STGMEDIUM * /* pmedium */,
                       BOOL /* fRelease */) override;
    STDMETHOD(EnumFormatEtc)(DWORD /* dwDirection */,
                             IEnumFORMATETC ** /* ppenumFormatEtc */) override;
    STDMETHOD(DAdvise)(FORMATETC *pformatetc, DWORD advf, IAdviseSink *pAdvSink,
                       DWORD *pdwConnection) override;
    STDMETHOD(DUnadvise)(DWORD dwConnection) override;
    STDMETHOD(EnumDAdvise)(IEnumSTATDATA **ppenumAdvise) override;

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
