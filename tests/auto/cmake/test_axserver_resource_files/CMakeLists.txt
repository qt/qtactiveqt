# Copyright (C) 2026 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required(VERSION 3.16)

project(test_axserver_resource_files LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 COMPONENTS Core Gui Widgets AxServer CONFIG REQUIRED)

foreach(var QT_AX_SERVER_RC_FILE QT_AX_SERVER_DEF_FILE QT_AX_SERVER_ICON_FILE)
    if(NOT EXISTS "${${var}}")
        message(FATAL_ERROR "${var} does not point to an existing file: '${${var}}'")
    endif()
endforeach()

# Not qt_add_axserver_library: its type library step needs midl, which MinGW CI lacks.
add_library(test_axserver_resource_files SHARED
    main.cpp
    ${QT_AX_SERVER_DEF_FILE}
    ${QT_AX_SERVER_RC_FILE}
)
target_link_libraries(test_axserver_resource_files PRIVATE
    Qt6::Core Qt6::Gui Qt6::Widgets Qt6::AxServer)
