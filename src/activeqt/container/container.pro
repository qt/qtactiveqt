TEMPLATE = lib

TARGET   = ActiveQt
CONFIG += qt_install_headers

SYNCQT.HEADER_FILES = qaxbase.h qaxobject.h qaxscript.h qaxselect.h qaxwidget.h
SYNCQT.HEADER_CLASSES = ../../../include/ActiveQt/QAxBase ../../../include/ActiveQt/QAxObject ../../../include/ActiveQt/QAxScriptEngine ../../../include/ActiveQt/QAxScript ../../../include/ActiveQt/QAxScriptManager ../../../include/ActiveQt/QAxSelect ../../../include/ActiveQt/QAxWidget
load(qt_installs)

TARGET   = QAxContainer

!debug_and_release|build_pass {
    CONFIG(debug, debug|release) {
        TARGET = $$member(TARGET, 0)d
    }
}

INCLUDEPATH *= $$QT.activeqt.includes

QT += core-private gui gui-private widgets widgets-private

CONFIG  += qt warn_on staticlib
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
