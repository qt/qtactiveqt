TEMPLATE = app
TARGET	 = simpleax

CONFIG	+= qt warn_off
QT += widgets axserver

SOURCES	 = main.cpp
RC_FILE  = simple.rc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/activeqt/simple
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS $$RC_FILE simple.ico simple.pro
sources.path = $$[QT_INSTALL_EXAMPLES]/activeqt/simple
INSTALLS += target sources
