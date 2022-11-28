// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

#include "sandboxing.h"
#include <memory>
#include <windows.h>
#include <sddl.h>
#include <userenv.h>


/** RAII class for temporarily impersonating low-integrity level for the current thread.
    Intended to be used together with CLSCTX_ENABLE_CLOAKING when creating COM objects.
    Based on "Designing Applications to Run at a Low Integrity Level" https://msdn.microsoft.com/en-us/library/bb625960.aspx */
class LowIntegrity : public Sandboxing
{
public:
    LowIntegrity()
    {
        HANDLE cur_token = nullptr;
        if (!OpenProcessToken(GetCurrentProcess(), TOKEN_DUPLICATE | TOKEN_ADJUST_DEFAULT | TOKEN_QUERY | TOKEN_ASSIGN_PRIMARY, &cur_token))
            qFatal("OpenProcessToken failed");

        if (!DuplicateTokenEx(cur_token, 0, nullptr, SecurityImpersonation, TokenPrimary, &m_token))
            qFatal("DuplicateTokenEx failed");

        CloseHandle(cur_token);

        PSID li_sid = nullptr;
        if (!ConvertStringSidToSid(L"S-1-16-4096", &li_sid)) // low integrity SID
            qFatal("ConvertStringSidToSid failed");

        // reduce process integrity level
        TOKEN_MANDATORY_LABEL TIL = {};
        TIL.Label.Attributes = SE_GROUP_INTEGRITY;
        TIL.Label.Sid = li_sid;
        if (!SetTokenInformation(m_token, TokenIntegrityLevel, &TIL, sizeof(TOKEN_MANDATORY_LABEL) + GetLengthSid(li_sid)))
            qFatal("SetTokenInformation failed");

        if (!ImpersonateLoggedOnUser(m_token)) // change current thread integrity
            qFatal("ImpersonateLoggedOnUser failed");

        LocalFree(li_sid);
        li_sid = nullptr;
    }

    ~LowIntegrity()
    {
        if (!RevertToSelf())
            qFatal("RevertToSelf failed");

        CloseHandle(m_token);
        m_token = nullptr;
    }

private:
    HANDLE m_token = nullptr;
};

std::unique_ptr<Sandboxing> Sandboxing::Create(QAxSelect::SandboxingLevel level)
{
    if (level == QAxSelect::SandboxingLowIntegrity)
        return std::make_unique<LowIntegrity>();

    Q_ASSERT_X(false, "Sandboxing::Create", "unknown sandboxing level");
    return {};
}
