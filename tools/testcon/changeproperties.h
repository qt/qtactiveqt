/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the tools applications of the Qt Toolkit.
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
****************************************************************************/

#ifndef CHANGEPROPERTIES_H
#define CHANGEPROPERTIES_H

#include <QtCore/qglobal.h>
#include "ui_changeproperties.h"

QT_BEGIN_NAMESPACE

class QAxWidget;

class ChangeProperties : public QDialog, Ui::ChangeProperties
{
    Q_OBJECT
public:
    ChangeProperties(QWidget *parent);

    void setControl(QAxWidget *control);

public slots:
    void updateProperties();

protected slots:
    void on_listProperties_currentItemChanged(QTreeWidgetItem *current);
    void on_listEditRequests_itemChanged(QTreeWidgetItem *item);
    void on_buttonSet_clicked();

private:
    QAxWidget *activex;
};

QT_END_NAMESPACE

#endif // CHANGEPROPERTIES_H
