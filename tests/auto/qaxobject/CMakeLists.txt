# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

# Generated from qaxobject.pro.

#####################################################################
## qaxobject Test:
#####################################################################

qt_internal_add_test(qaxobject # special case
    SOURCES
        tst_qaxobject.cpp
    PUBLIC_LIBRARIES
        Qt::AxContainer
        Qt::Gui
)
