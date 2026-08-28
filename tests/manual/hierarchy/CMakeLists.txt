# Copyright (C) 2023 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

if(NOT QT_BUILD_STANDALONE_TESTS AND NOT QT_BUILDING_QT)
    cmake_minimum_required(VERSION 3.16)
    project(tst_hierarchy LANGUAGES CXX)
    find_package(Qt6BuildInternals REQUIRED COMPONENTS STANDALONE_TEST)
endif()

#####################################################################
## hierarchy Library:
#####################################################################

set(CMAKE_AUTOMOC ON)

qt_internal_add_manual_test(tst_hierarchy
    GUI
    SOURCES
        main.cpp
        objects.cpp objects.h
        hierarchy.def
        hierarchy.rc
    LIBRARIES
        Qt::AxServer
        Qt::Gui
        Qt::Widgets
)

qt_disable_warnings(tst_hierarchy)
qt6_target_idl(tst_hierarchy)
