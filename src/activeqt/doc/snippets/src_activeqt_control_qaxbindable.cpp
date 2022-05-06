/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the documentation of the Qt Toolkit.
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

//! [0]
class MyActiveX : public QWidget, public QAxBindable
{
    Q_OBJECT
    Q_PROPERTY(int value READ value WRITE setValue)

public:
    MyActiveX(QWidget *parent = 0);
    ...

    int value() const;
    void setValue(int);
};
//! [0]


//! [1]
void MyActiveQt::setText(const QString &text)
{
    if (!requestPropertyChange("text"))
        return;

    // update property

    propertyChanged("text");
}
//! [1]


//! [2]
long AxImpl::queryInterface(const QUuid &iid, void **iface)
{
    *iface = 0;
    if (iid == IID_ISomeCOMInterface)
        *iface = (ISomeCOMInterface*)this;
    else
        return E_NOINTERFACE;

    AddRef();
    return S_OK;
}
//! [2]


//! [3]
HRESULT AxImpl::QueryInterface(REFIID iid, void **iface)
{
    return controllingUnknown()->QueryInterface(iid, iface);
}

ulong AxImpl::AddRef()
{
    return controllingUnknown()->AddRef();
}

ulong AxImpl::Release()
{
    return controllingUnknown()->Release();
}
//! [3]
