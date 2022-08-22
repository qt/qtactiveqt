# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

# Generated from qaxobject.pro.

#####################################################################
## qaxobject Test:
#####################################################################

qt_internal_add_test(qaxobject # special case
    SOURCES
        tst_qaxobject.cpp
    LIBRARIES
        Qt::AxContainer
        Qt::Gui
)
