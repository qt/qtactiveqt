// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

#ifndef SANDBOXING_H
#define SANDBOXING_H
#include <windows.h>

/** RAII class for temporarily impersonating low-integrity level for the current thread.
    Intended to be used together with CLSCTX_ENABLE_CLOAKING when creating COM objects.
    Based on "Designing Applications to Run at a Low Integrity Level" https://msdn.microsoft.com/en-us/library/bb625960.aspx */
struct LowIntegrity {
    LowIntegrity();

    ~LowIntegrity();

private:
    HANDLE m_token = nullptr;
};

#endif // SANDBOXING_H
