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

#ifndef QAXSELECT_H
#define QAXSELECT_H
#include <QtWidgets/qdialog.h>

QT_BEGIN_NAMESPACE

class QAxSelectPrivate;
class QModelIndex;

class QAxSelect : public QDialog
{
    Q_OBJECT
public:
    enum SandboxingLevel {
        SandboxingNone = 0,
        SandboxingProcess,
        SandboxingLowIntegrity,
    };

    explicit QAxSelect(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
    ~QAxSelect() override;

    QString clsid() const;
    SandboxingLevel sandboxingLevel() const;

private Q_SLOTS:
    void onActiveXListCurrentChanged(const QModelIndex &);
    void onActiveXListActivated();
    void onFilterLineEditChanged(const QString &);

private:
    QScopedPointer<QAxSelectPrivate> d;
};

QT_END_NAMESPACE

#endif // QAXSELECT_H
