TEMPLATE = app

CONFIG	+= qaxserver qaxserver_no_postlink qaxcontainer
QT += widgets printsupport

# ui_qaxselect.h
INCLUDEPATH += $$QT.activeqt.sources/../../tools/container/debug \
    $$QT.activeqt.sources/../../tools/container/release \
    $$QT.activeqt.sources/container \

SOURCES	 = main.cpp docuwindow.cpp mainwindow.cpp invokemethod.cpp changeproperties.cpp ambientproperties.cpp controlinfo.cpp
HEADERS	 = docuwindow.h mainwindow.h invokemethod.h changeproperties.h ambientproperties.h controlinfo.h
FORMS	 = mainwindow.ui invokemethod.ui changeproperties.ui ambientproperties.ui controlinfo.ui
RC_FILE	 = testcon.rc

win32-borland {
    QMAKE_POST_LINK = -midl $$QT.activeqt.sources/../../tools/testcon/testcon.idl
} else {
    !win32-g++*:QMAKE_POST_LINK = midl $$QT.activeqt.sources/../../tools/testcon/testcon.idl && move testcon.tlb $(TARGETDIR)

}

target.path = $$[QT_INSTALL_BINS]
INSTALLS += target
