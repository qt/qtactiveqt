// Copyright (C) 2026 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QAxFactory>
#include <QWidget>

class TestWidget : public QWidget
{
    Q_OBJECT
    Q_CLASSINFO("ClassID", "{5d1a0f1e-3b6c-4a4e-9c7a-2f8e1b0d4c11}")
    Q_CLASSINFO("InterfaceID", "{8a3f6b2c-1d4e-4f5a-b6c7-d8e9f0a1b2c3}")
    Q_CLASSINFO("EventsID", "{c4d5e6f7-0819-4a2b-8c3d-4e5f60718293}")
public:
    explicit TestWidget(QWidget *parent = nullptr) : QWidget(parent) { }
};

QAXFACTORY_DEFAULT(TestWidget, "{5d1a0f1e-3b6c-4a4e-9c7a-2f8e1b0d4c11}",
                   "{8a3f6b2c-1d4e-4f5a-b6c7-d8e9f0a1b2c3}",
                   "{c4d5e6f7-0819-4a2b-8c3d-4e5f60718293}",
                   "{2b3c4d5e-6f70-4182-93a4-b5c6d7e8f901}",
                   "{9f8e7d6c-5b4a-4392-8170-6f5e4d3c2b1a}")

#include "main.moc"
