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

#include <qapplication.h>
#include <private/qcoreapplication_p.h>
#include <qwidget.h>
#include <qdir.h>

#include <qt_windows.h>

#include "qclassfactory_p.h"

QT_BEGIN_NAMESPACE

bool qax_ownQApp = false;
HHOOK qax_hhook = nullptr;

// in qaxserver.cpp
extern wchar_t qAxModuleFilename[MAX_PATH];
extern bool qAxIsServer;
extern ITypeLib *qAxTypeLibrary;
extern unsigned long qAxLockCount();
extern QString qAxInit();
extern void qAxCleanup();
extern HANDLE qAxInstance;
static uint qAxThreadId = 0;

extern HRESULT UpdateRegistry(bool bRegister, bool perUser);
extern HRESULT GetClassObject(const GUID &clsid, const GUID &iid, void **ppUnk);

STDAPI DllRegisterServer()
{
    return UpdateRegistry(true, false);
}

STDAPI DllUnregisterServer()
{
    return UpdateRegistry(false, false);
}

STDAPI DllInstall(BOOL bInstall, LPCWSTR pszCmdLine) {
    bool perUser = false; // per-user (un)registration
    if (pszCmdLine) {
        if (QStringView(pszCmdLine).compare(u"user", Qt::CaseInsensitive) == 0)
            perUser = true;
    }

    if (bInstall) {
        HRESULT hr = UpdateRegistry(true, perUser);
        if (FAILED(hr))
            UpdateRegistry(false, perUser);
        return hr;
    } else {
        return UpdateRegistry(false, perUser);
    }
}

STDAPI DllGetClassObject(const GUID &clsid, const GUID &iid, void** ppv)
{
    if (!qAxThreadId)
        qAxThreadId = GetCurrentThreadId();
    else if (GetCurrentThreadId() != qAxThreadId)
        return E_FAIL;

    GetClassObject(clsid, iid, ppv);
    if (!*ppv)
        return CLASS_E_CLASSNOTAVAILABLE;
    return S_OK;
}

STDAPI DllCanUnloadNow()
{
    if (GetCurrentThreadId() != qAxThreadId)
        return S_FALSE;
    if (qAxLockCount())
        return S_FALSE;
    if (!qax_ownQApp)
        return S_OK;

    // check if qApp still runs widgets (in other DLLs)
    QWidgetList widgets = QApplication::allWidgets();
    int count = widgets.count();
    for (int w = 0; w < widgets.count(); ++w) {
        // remove all Qt generated widgets
        QWidget *widget = widgets.at(w);
        if (widget->windowType() == Qt::Desktop || widget->objectName() == QLatin1String("Qt internal tablet widget"))
            count--;
    }
    if (count)
        return S_FALSE;

    // no widgets left - destroy qApp
    if (qax_hhook)
        UnhookWindowsHookEx(qax_hhook);

    QClassFactory::cleanupCreatedApplication(*qApp);
    delete qApp;
    qax_ownQApp = false;

    // never allow unloading - safety net for Internet Explorer
    return S_FALSE;
}


EXTERN_C BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /* lpvReserved */)
{
    GetModuleFileName(hInstance, qAxModuleFilename, MAX_PATH);
    // Point QApplication here such that the directory is added to the patch, and qt.conf and
    // deployed plugins are found.
    QCoreApplicationPrivate::setApplicationFilePath(QDir::cleanPath(QString::fromWCharArray(qAxModuleFilename)));

    qAxInstance = hInstance;
    qAxIsServer = true;

    if (dwReason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hInstance);
        qAxInit();
    } else if (dwReason == DLL_PROCESS_DETACH) {
        qAxCleanup();
    }

    return true;
}

QT_END_NAMESPACE
