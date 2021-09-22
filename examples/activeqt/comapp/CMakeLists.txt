# Generated from comapp.pro.

cmake_minimum_required(VERSION 3.16)
project(comapp LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
  set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/activeqt/comapp")

find_package(Qt6 COMPONENTS Core Gui AxServer Widgets)
qt6_add_axserver_executable(comapp
    main.cpp
    comapp.rc
)
target_link_libraries(comapp PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
)

install(TARGETS comapp
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
