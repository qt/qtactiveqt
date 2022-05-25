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
Outlook::Application *outlook = new Outlook::Application;
//! [0]


//! [1]
Outlook::_NameSpace *session = outlook->Session();
//! [1]


//! [2]
Outlook::NameSpace *session = outlook->Session();
//! [2]


//! [3]
Outlook::_NameSpace *tmp = outlook->Session();
Outlook::NameSpace *session = new Outlook::NameSpace(tmp);
delete tmp; // or any other use of tmp: segfault
//! [3]


//! [4]
Outlook::NameSpace *session = new Outlook::NameSpace(outlook->Session());
//! [4]
