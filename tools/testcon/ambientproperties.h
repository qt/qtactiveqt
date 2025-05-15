// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial

#ifndef AMBIENTPROPERTIES_H
#define AMBIENTPROPERTIES_H

#include <QtCore/qglobal.h>

#include "ui_ambientproperties.h"

QT_BEGIN_NAMESPACE

class AmbientProperties : public QDialog, Ui::AmbientProperties
{
    Q_OBJECT
public:
    AmbientProperties(QWidget *parent);

    void setControl(QWidget *widget);

public slots:
    void on_buttonBackground_clicked();
    void on_buttonForeground_clicked();
    void on_buttonFont_clicked();
    void on_buttonEnabled_toggled(bool on);

private:
    QWidgetList mdiAreaWidgets() const;

    QWidget *container;
};

QT_END_NAMESPACE

#endif // AMBIENTPROPERTIES_H
