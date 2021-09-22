# Generated from wrapper.pro.

cmake_minimum_required(VERSION 3.16)
project(wrapperax LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
  set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/activeqt/wrapper")

find_package(Qt6 COMPONENTS Core Gui Widgets AxServer)

qt6_add_axserver_library(wrapperax
    main.cpp
    wrapperax.def
    wrapperax.rc
)
target_link_libraries(wrapperax PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
)

install(TARGETS wrapperax
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
