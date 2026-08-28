# Copyright (C) 2023 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

if(NOT QT_BUILD_STANDALONE_TESTS AND NOT QT_BUILDING_QT)
    cmake_minimum_required(VERSION 3.16)
    project(tst_opengl LANGUAGES CXX)
    find_package(Qt6BuildInternals REQUIRED COMPONENTS STANDALONE_TEST)
endif()

#####################################################################
## testcontrol Binary:
#####################################################################

set(CMAKE_AUTOMOC ON)

qt_internal_add_manual_test(tst_opengl
    GUI
    SOURCES
        glbox.cpp glbox.h
        globjwin.cpp globjwin.h
        main.cpp
        opengl.def
        opengl.rc
    LIBRARIES
        Qt::AxServer
        Qt::Gui
        Qt::OpenGL
        Qt::OpenGLWidgets
        Qt::Widgets
)

# qt_disable_warnings(tst_opengl)
qt6_target_idl(tst_opengl)
