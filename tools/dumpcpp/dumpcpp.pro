TEMPLATE = app

CONFIG  += console qaxcontainer
QT += widgets

SOURCES += main.cpp

target.path = $$[QT_INSTALL_BINS]
INSTALLS += target
