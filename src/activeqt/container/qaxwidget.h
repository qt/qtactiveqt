/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
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
****************************************************************************/

#ifndef QAXWIDGET_H
#define QAXWIDGET_H

#include <ActiveQt/qaxbase.h>
#include <QtWidgets/qwidget.h>

QT_BEGIN_NAMESPACE

class QAxHostWindow;
class QAxAggregated;

class QAxClientSite;
class QAxWidgetPrivate;

class QAxWidget : public QWidget, public QAxBase
{
    Q_OBJECT_FAKE
public:
    QObject* qObject() const override { return const_cast<QAxWidget *>(this); }
    const char *className() const override;

    explicit QAxWidget(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    explicit QAxWidget(const QString &c, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    explicit QAxWidget(IUnknown *iface, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~QAxWidget() override;

    void clear() override;
    bool doVerb(const QString &verb);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

    virtual QAxAggregated *createAggregate();

protected:
    bool initialize(IUnknown **) override;
    virtual bool createHostWindow(bool);
    bool createHostWindow(bool, const QByteArray&);

    void changeEvent(QEvent *e) override;
    void resizeEvent(QResizeEvent *) override;

    virtual bool translateKeyEvent(int message, int keycode) const;

    void connectNotify(const QMetaMethod &signal) override;
    const QMetaObject *fallbackMetaObject() const override;
private:
    friend class QAxClientSite;
    QAxClientSite *container = nullptr;

    QAxWidgetPrivate *m_unused = nullptr;
    const QMetaObject *parentMetaObject() const override;
};

template <> inline QAxWidget *qobject_cast<QAxWidget*>(const QObject *o)
{
    void *result = o ? const_cast<QObject *>(o)->qt_metacast("QAxWidget") : nullptr;
    return static_cast<QAxWidget *>(result);
}

template <> inline QAxWidget *qobject_cast<QAxWidget*>(QObject *o)
{
    void *result = o ? o->qt_metacast("QAxWidget") : nullptr;
    return static_cast<QAxWidget *>(result);
}

QT_END_NAMESPACE

#endif // QAXWIDGET_H
