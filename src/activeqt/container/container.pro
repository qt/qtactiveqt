TARGET   = QAxContainer

QT += core-private gui gui-private widgets widgets-private axbase
CONFIG  += static

LIBS    += -lole32 -loleaut32
!wince*:LIBS    += -luser32 -lgdi32 -ladvapi32
win32-g++*:LIBS += -luuid

HEADERS =   ../control/qaxaggregated.h \
            qaxbase.h \
            qaxwidget.h \
            qaxobject.h \
            qaxscript.h \
            qaxselect.h \
            ../shared/qaxtypes.h

SOURCES =   qaxbase.cpp \
            qaxdump.cpp \
            qaxwidget.cpp \
            qaxobject.cpp \
            qaxscript.cpp \
            qaxscriptwrapper.cpp \
            qaxselect.cpp \
            ../shared/qaxtypes.cpp

FORMS =     qaxselect.ui

MODULE = axcontainer
MODULE_CONFIG = dumpcpp
CONFIG += no_module_headers
load(qt_module)
# QtActiveQt is too inconsistent with other Qt modules
# to use the generic cmake config files generator
CONFIG -= create_cmake
DEFINES -= QT_NO_CAST_TO_ASCII QT_USE_QSTRINGBUILDER
