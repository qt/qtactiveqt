TEMPLATE = lib
TARGET	 = wrapperax

CONFIG += qt warn_off dll
QT += widgets axserver

contains(CONFIG, static):DEFINES += QT_NODLL

SOURCES	 = main.cpp
RC_FILE	 = wrapperax.rc
DEF_FILE = wrapperax.def

# install
target.path = $$[QT_INSTALL_EXAMPLES]/activeqt/wrapper
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS $$RC_FILE $$DEF_FILE wrapperax.ico wrapper.pro
sources.path = $$[QT_INSTALL_EXAMPLES]/activeqt/wrapper
INSTALLS += target sources
