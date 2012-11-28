TEMPLATE = lib
TARGET	 = hierarchyax

CONFIG += qt warn_off dll
QT += widgets axserver

SOURCES	 = objects.cpp main.cpp
HEADERS	 = objects.h
RC_FILE  = hierarchy.rc
DEF_FILE = hierarchy.def

# install
target.path = $$[QT_INSTALL_EXAMPLES]/activeqt/hierarchy
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS $$RC_FILE $$DEF_FILE hierarchy.ico hierarchy.pro
sources.path = $$[QT_INSTALL_EXAMPLES]/activeqt/hierarchy
INSTALLS += target sources
