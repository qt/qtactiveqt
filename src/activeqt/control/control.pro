TEMPLATE = lib
TARGET   = QAxServer
CONFIG  += create_prl

MODULE = QAxServer
load(qt_module)
DEFINES -= QT_NO_CAST_TO_ASCII QT_ASCII_CAST_WARNINGS QT_USE_QSTRINGBUILDER

INCLUDEPATH *= $$QT.activeqt.includes

QT += core-private gui-private widgets
CONFIG  += qt warn_off static
DESTDIR  = $$QT.activeqt.libs

DEFINES	+= QAX_SERVER
win32-g++*:DEFINES += QT_NEEDS_QMAIN

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

