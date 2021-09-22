# Generated from simpleqml.pro.

cmake_minimum_required(VERSION 3.16)
project(simpleqmlax LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
  set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/activeqt/simpleqml")

find_package(Qt6 COMPONENTS Core Gui Widgets AxServer Quick QuickWidgets)
qt6_add_axserver_library(simpleqmlax
    main.cpp
    simpleqml.def
    simpleqml.rc
)
target_link_libraries(simpleqmlax PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Quick
    Qt::QuickWidgets
    Qt::Widgets
)

# Resources:
set(simpleqml_resource_files
    "main.qml"
)

qt6_add_resources(simpleqmlax "simpleqml"
    PREFIX
        "/"
    FILES
        ${simpleqml_resource_files}
)

install(TARGETS simpleqmlax
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
