TEMPLATE = lib
TARGET	 = wrapperax

CONFIG += qt warn_off dll
QT += widgets axserver

SOURCES	 = main.cpp
RC_FILE	 = wrapperax.rc
DEF_FILE = wrapperax.def

# install
target.path = $$[QT_INSTALL_EXAMPLES]/activeqt/wrapper
INSTALLS += target
