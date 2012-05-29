TEMPLATE = lib
TARGET   = QAxServer
CONFIG  += create_prl

!debug_and_release|build_pass {
   CONFIG(debug, debug|release) {
      TARGET = $$member(TARGET, 0)d
   }
}

INCLUDEPATH *= $$QT.activeqt.includes

QT += core-private gui-private widgets
CONFIG  += qt warn_off static
DESTDIR  = $$QT.activeqt.libs

DEFINES	+= QAX_SERVER
win32-g++*:DEFINES += QT_NEEDS_QMAIN
win32-borland:DEFINES += QT_NEEDS_QMAIN

LIBS    += -luser32 -lole32 -loleaut32 -lgdi32
win32-g++*:LIBS += -luuid

HEADERS =   qaxaggregated.h \
            qaxbindable.h \
            qaxfactory.h \
            ../shared/qaxtypes.h \
            ../shared/qaxutils_p.h

SOURCES =   qaxserver.cpp \
            qaxserverbase.cpp \
            qaxbindable.cpp \
            qaxfactory.cpp \
            qaxservermain.cpp \
            qaxserverdll.cpp \
            qaxmain.cpp \
            ../shared/qaxtypes.cpp \
            ../shared/qaxutils.cpp

load(qt_installs)
