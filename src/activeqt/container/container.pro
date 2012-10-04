TEMPLATE = lib
TARGET   = QAxContainer
CONFIG  += create_prl

MODULE = QAxContainer
load(qt_module)
DEFINES -= QT_NO_CAST_TO_ASCII QT_ASCII_CAST_WARNINGS QT_USE_QSTRINGBUILDER

INCLUDEPATH *= $$QT.activeqt.includes

QT += core-private gui gui-private widgets widgets-private

CONFIG  += qt warn_on static
DESTDIR  = $$QT.activeqt.libs

LIBS    += -lole32 -loleaut32
!wince*:LIBS    += -luser32 -lgdi32 -ladvapi32
win32-g++*:LIBS += -luuid

HEADERS =   ../control/qaxaggregated.h \
            qaxbase.h \
            qaxwidget.h \
            qaxobject.h \
            qaxscript.h \
            qaxselect.h \
            ../shared/qaxtypes.h \
            ../shared/qaxutils_p.h

SOURCES =   qaxbase.cpp \
            qaxdump.cpp \
            qaxwidget.cpp \
            qaxobject.cpp \
            qaxscript.cpp \
            qaxscriptwrapper.cpp \
            qaxselect.cpp \
            ../shared/qaxtypes.cpp \
            ../shared/qaxutils.cpp

FORMS =     qaxselect.ui

