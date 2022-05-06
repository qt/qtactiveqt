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

#ifndef QAXBINDABLE_H
#define QAXBINDABLE_H

#include <QtWidgets/qwidget.h>

struct IUnknown;

QT_BEGIN_NAMESPACE

class QAxAggregated;
class QIODevice;
struct IAxServerBase;

class QAxBindable
{
    Q_DISABLE_COPY_MOVE(QAxBindable)
    friend class QAxServerBase;
public:
    QAxBindable();
    virtual ~QAxBindable();

    virtual QAxAggregated *createAggregate();
    void reportError(int code, const QString &src, const QString &desc, const QString &help = QString());

    virtual bool readData(QIODevice *source, const QString &format);
    virtual bool writeData(QIODevice *sink);

protected:
    bool requestPropertyChange(const char *property);
    void propertyChanged(const char *property);

    IUnknown *clientSite() const;

private:
    IAxServerBase *activex = nullptr;
};

QT_END_NAMESPACE

#endif // QAXBINDABLE_H
