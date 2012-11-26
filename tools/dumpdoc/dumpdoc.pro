TEMPLATE = app

CONFIG  += console
QT += axcontainer widgets

SOURCES += main.cpp

target.path = $$[QT_INSTALL_BINS]
INSTALLS += target

