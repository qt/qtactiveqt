TEMPLATE = lib
TARGET   = QAxContainer
CONFIG  += create_prl

contains(QT_CONFIG, debug_and_release):CONFIG += debug_and_release
contains(QT_CONFIG, build_all):CONFIG += build_all

!debug_and_release|build_pass {
    CONFIG(debug, debug|release) {
        TARGET = $$member(TARGET, 0)d
    }
}

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

load(qt_installs)
