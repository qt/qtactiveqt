# Generated from qutlook.pro.

cmake_minimum_required(VERSION 3.14)
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

)
set_target_properties(qutlook PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)
target_link_libraries(qutlook PUBLIC
    Qt::AxContainer
    Qt::Core
    Qt::Gui
    Qt::Widgets
)

if(NOT TYPELIBS_ISEMPTY)
    target_sources(qutlook PUBLIC
        addressview.cpp addressview.h
        main.cpp
    )
endif()

install(TARGETS qutlook
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
