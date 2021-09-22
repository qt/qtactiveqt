# Generated from simple.pro.

cmake_minimum_required(VERSION 3.16)
project(simpleax LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
  set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/activeqt/simple")

find_package(Qt6 COMPONENTS Core Gui Widgets AxServer)
qt6_add_axserver_executable(simpleax
    main.cpp
    simple.def
    simple.rc
)
target_link_libraries(simpleax PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
)

install(TARGETS simpleax
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
