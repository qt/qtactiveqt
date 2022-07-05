# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

cmake_minimum_required(VERSION 3.16)

project(cmake_axserver)

find_package(Qt6 COMPONENTS Core Gui Widgets AxServer CONFIG REQUIRED)
add_executable(axserverapp WIN32 axserver.cpp)
target_link_libraries(axserverapp Qt6::Core Qt6::Gui Qt6::Widgets Qt6::AxServer)
