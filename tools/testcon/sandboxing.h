// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial

#ifndef SANDBOXING_H
#define SANDBOXING_H
#include <QString>
#include <QAxSelect>


class Sandboxing
{
public:
    static std::unique_ptr<Sandboxing> Create(QAxSelect::SandboxingLevel level, const QString &clsid);

    Sandboxing() {}

    virtual ~Sandboxing() {}
};

#endif // SANDBOXING_H
