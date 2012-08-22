TEMPLATE = lib
TARGET	 = hierarchyax

CONFIG	+= qt warn_off qaxserver dll
contains(CONFIG, static):DEFINES += QT_NODLL
QT += widgets

SOURCES	 = objects.cpp main.cpp
HEADERS	 = objects.h
RC_FILE  = hierarchy.rc
DEF_FILE = qaxserver.def

# install
target.path = $$[QT_INSTALL_EXAMPLES]/activeqt/hierarchy
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS $$RC_FILE $$DEF_FILE qaxserver.ico hierarchy.pro
sources.path = $$[QT_INSTALL_EXAMPLES]/activeqt/hierarchy
INSTALLS += target sources
