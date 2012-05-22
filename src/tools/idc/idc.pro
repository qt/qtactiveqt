TEMPLATE        = app
CONFIG         += console

QT -= gui

SOURCES         = main.cpp
DESTDIR         = $$QT.activeqt.bins

target.path = $$[QT_INSTALL_BINS]
INSTALLS += target
