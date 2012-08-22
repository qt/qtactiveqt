TEMPLATE = app
TARGET	 = menusax

CONFIG	+= qt warn_off qaxserver
QT += widgets

SOURCES	 = main.cpp menus.cpp
HEADERS	 = menus.h
RC_FILE  = menus.rc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/activeqt/menus
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS $$RC_FILE qaxserver.ico menus.pro
sources.path = $$[QT_INSTALL_EXAMPLES]/activeqt/menus
INSTALLS += target sources
