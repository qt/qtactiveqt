TARGET  = QtAxBase
MODULE  = axbase

QT     += core-private gui-private widgets
CONFIG += static internal_module

load(qt_module)

LIBS_PRIVATE += -lole32 -loleaut32 -luser32 -lgdi32 -ladvapi32
mingw: LIBS_PRIVATE += -luuid

HEADERS = \
    qaxtypefunctions_p.h \
    qaxutils_p.h

SOURCES = \
    qaxtypefunctions.cpp \
    qaxutils.cpp
