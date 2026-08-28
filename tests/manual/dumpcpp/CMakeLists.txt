# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

if(NOT QT_BUILD_STANDALONE_TESTS AND NOT QT_BUILDING_QT)
    cmake_minimum_required(VERSION 3.16)
    project(tst_dumpcpp_manual LANGUAGES CXX)
    find_package(Qt6BuildInternals REQUIRED COMPONENTS STANDALONE_TEST)
endif()

#####################################################################
## dumpcpp Binary:
#####################################################################

qt_internal_add_manual_test(tst_dumpcpp_manual
    SOURCES
        ../shared/metaobjectdump.cpp ../shared/metaobjectdump.h
        ../shared/textdialog.cpp ../shared/textdialog.h
        main.cpp
    INCLUDE_DIRECTORIES
        ../shared
    LIBRARIES
        Qt::AxContainer
        Qt::Gui
        Qt::Test
        Qt::Widgets
)

qt6_target_typelibs(tst_dumpcpp_manual LIBRARIES "ieframe.dll")
