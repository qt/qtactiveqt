# Copyright (C) 2023 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

if(NOT QT_BUILD_STANDALONE_TESTS AND NOT QT_BUILDING_QT)
    cmake_minimum_required(VERSION 3.16)
    project(tst_menus LANGUAGES CXX)
    find_package(Qt6BuildInternals REQUIRED COMPONENTS STANDALONE_TEST)
endif()

#####################################################################
## menus Executable:
#####################################################################

set(CMAKE_AUTOMOC ON)

qt_internal_add_manual_test(tst_menus
    GUI
    SOURCES
        main.cpp
        menus.cpp menus.h
        menus.def
        menus.rc
    LIBRARIES
        Qt::AxServer
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

qt_disable_warnings(tst_menus)
qt6_target_idl(tst_menus)
