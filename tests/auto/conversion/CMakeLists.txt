# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

# Generated from conversion.pro.

#####################################################################
## conversion Test:
#####################################################################

qt_internal_add_test(conversion # special case
    SOURCES
        tst_conversion.cpp
    LIBRARIES
        Qt::AxContainer
        Qt::Gui
)
