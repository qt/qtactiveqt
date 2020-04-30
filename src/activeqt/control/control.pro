TARGET   = QtAxServer

QT += widgets
QT_PRIVATE += core-private gui-private widgets-private axbase-private
CONFIG  += static

DEFINES += QAX_SERVER

mingw: DEFINES += QT_NEEDS_QMAIN

HEADERS =   qaxaggregated.h \
            qaxbindable.h \
            qaxfactory.h \
            qclassfactory_p.h \
            ../shared/qaxtypes_p.h

SOURCES =   qaxaggregated.cpp \
            qaxserver.cpp \
            qaxserverbase.cpp \
            qaxbindable.cpp \
            qaxfactory.cpp \
            qaxservermain.cpp \
            qaxserverdll.cpp \
            qaxmain.cpp \
            ../shared/qaxtypes.cpp

LIBS += -lshell32

MODULE = axserver
MODULE_DEFINES = QAXSERVER
MODULE_CONFIG = idcidl force_import_plugins
load(qt_module)
