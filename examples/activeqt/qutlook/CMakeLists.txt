# Generated from qutlook.pro.

cmake_minimum_required(VERSION 3.16)
project(qutlook LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
  set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/activeqt/qutlook")

find_package(Qt6 COMPONENTS Core)
find_package(Qt6 COMPONENTS Gui)
find_package(Qt6 COMPONENTS Widgets)
find_package(Qt6 COMPONENTS AxContainer)

qt_add_executable(qutlook
    addressview.cpp addressview.h
    main.cpp
)

set_target_properties(qutlook PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

qt6_target_typelibs(qutlook LIBRARIES "msoutl:{00062FFF-0000-0000-C000-000000000046}")

target_link_libraries(qutlook PUBLIC
    Qt::AxContainer
    Qt::Core
    Qt::Gui
    Qt::Widgets
)

install(TARGETS qutlook
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
