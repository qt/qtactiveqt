TEMPLATE        = app
CONFIG         += console

QT -= gui

SOURCES         = main.cpp

DESTDIR         = $$[QT_INSTALL_BINS]
target.path = $$[QT_INSTALL_BINS]
INSTALLS += target
