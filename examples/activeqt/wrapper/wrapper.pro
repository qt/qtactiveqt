TEMPLATE = lib
TARGET	 = wrapperax

CONFIG	+= qt warn_off qaxserver dll
QT += widgets

contains(CONFIG, static):DEFINES += QT_NODLL

SOURCES	 = main.cpp
RC_FILE	 = wrapperax.rc
DEF_FILE = qaxserver.def

# install
target.path = $$[QT_INSTALL_EXAMPLES]/activeqt/wrapper
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS $$RC_FILE $$DEF_FILE qaxserver.ico wrapper.pro
sources.path = $$[QT_INSTALL_EXAMPLES]/activeqt/wrapper
INSTALLS += target sources
