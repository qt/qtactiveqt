# Copyright (C) 2023 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

if(NOT QT_BUILD_STANDALONE_TESTS AND NOT QT_BUILDING_QT)
    cmake_minimum_required(VERSION 3.16)
    project(tst_multiple LANGUAGES CXX)
    find_package(Qt6BuildInternals REQUIRED COMPONENTS STANDALONE_TEST)
endif()

#####################################################################
## multiple Binary:
#####################################################################

set(CMAKE_AUTOMOC ON)

qt_internal_add_manual_test(tst_multiple
    GUI
    SOURCES
        ax1.h
        ax2.h
        main.cpp
        multipleax.def
        multipleax.rc
    LIBRARIES
        Qt::AxServer
        Qt::Gui
        Qt::Widgets

)
# qt_disable_warnings(tst_multiple)
qt6_target_idl(tst_multiple)
