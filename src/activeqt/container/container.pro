TARGET   = QtAxContainer

QT += widgets
QT_PRIVATE += core-private gui-private widgets-private axbase-private
CONFIG  += static

HEADERS =   ../control/qaxaggregated.h \
            qaxbase.h \
            qaxbase_p.h \
            qaxwidget.h \
            qaxobject.h \
            qaxscript.h \
            qaxselect.h \
            ../shared/qaxtypes_p.h

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
load(qt_module)
