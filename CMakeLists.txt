# Generated from qtactiveqt.pro.

cmake_minimum_required(VERSION 3.16)

include(".cmake.conf")
project(QtActiveQt # special case
    VERSION "${QT_REPO_MODULE_VERSION}"
    DESCRIPTION "Qt Active Qt Libraries" # special case
    HOMEPAGE_URL "https://qt.io/"
    LANGUAGES CXX C
)

if (NOT WIN32)
    message(NOTICE "Condition \"WIN32\" is not met, enabling documentation build only.")
    # special case begin
    set(QT_NO_INTERNAL_COMPATIBILITY_FUNCTIONS TRUE)
    find_package(Qt6 ${PROJECT_VERSION} CONFIG REQUIRED COMPONENTS BuildInternals)
    qt_build_repo_begin()
    add_subdirectory(src/activeqt/doc)
    qt_build_repo_end()
    # special case end
    return()
endif()

find_package(Qt6 ${PROJECT_VERSION} CONFIG REQUIRED COMPONENTS BuildInternals Core) # special case
find_package(Qt6 ${PROJECT_VERSION} CONFIG OPTIONAL_COMPONENTS Qml Quick Gui Widgets PrintSupport) # special case

if(NOT TARGET Qt::Gui OR NOT TARGET Qt::Widgets OR NOT TARGET Qt::PrintSupport)
    message(NOTICE "Skipping the build as the condition \"TARGET Qt::Gui\", \"TARGET Qt::Widget\" "
            "or \"TARGET Qt::Printsupport\" is not met.")
    return()
endif()

qt_build_repo()
