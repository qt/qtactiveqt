# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

if(NOT QT_BUILD_STANDALONE_TESTS AND NOT QT_BUILDING_QT)
    cmake_minimum_required(VERSION 3.16)
    project(tst_testcontrol_manual LANGUAGES CXX)
    find_package(Qt6BuildInternals REQUIRED COMPONENTS STANDALONE_TEST)
endif()

#####################################################################
## testcontrol Binary:
#####################################################################

qt_internal_add_manual_test(tst_testcontrol_manual
    GUI
    SOURCES
        main.cpp
        testcontrol.rc
    LIBRARIES
        Qt::AxServer
        Qt::Gui
        Qt::Widgets
)
qt_disable_warnings(tst_testcontrol_manual)
qt6_target_idl(tst_testcontrol_manual)
