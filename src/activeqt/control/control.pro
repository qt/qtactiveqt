TARGET   = QAxServer

QT += core-private gui-private widgets axbase
CONFIG  += static

DEFINES	+= QAX_SERVER
win32-g++*:DEFINES += QT_NEEDS_QMAIN

LIBS    += -luser32 -lole32 -loleaut32 -lgdi32
win32-g++*:LIBS += -luuid

HEADERS =   qaxaggregated.h \
            qaxbindable.h \
            qaxfactory.h \
            ../shared/qaxtypes.h

SOURCES =   qaxserver.cpp \
            qaxserverbase.cpp \
            qaxbindable.cpp \
            qaxfactory.cpp \
            qaxservermain.cpp \
            qaxserverdll.cpp \
            qaxmain.cpp \
            ../shared/qaxtypes.cpp

MODULE = axserver
MODULE_DEFINES = QAXSERVER
MODULE_CONFIG = idcidl
CONFIG  += no_module_headers
load(qt_module)
DEFINES -= QT_NO_CAST_TO_ASCII QT_USE_QSTRINGBUILDER
