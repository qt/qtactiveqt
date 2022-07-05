# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

# Generated from auto.pro.

add_subdirectory(conversion)
add_subdirectory(qaxobject)
add_subdirectory(dumpcpp)
add_subdirectory(cmake)
if(NOT GCC)
    add_subdirectory(qaxscript)
endif()
