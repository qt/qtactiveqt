# Generated from testcon.pro.

#####################################################################
## testcon Binary:
#####################################################################

qt_internal_add_app(testcon # special case
#    OUTPUT_DIRECTORY "$$[QT_INSTALL_BINS]" # special case
#    INSTALL_DIRECTORY "$$[QT_INSTALL_BINS]" # special case
    SOURCES
        ambientproperties.cpp ambientproperties.h ambientproperties.ui
        changeproperties.cpp changeproperties.h changeproperties.ui
        controlinfo.cpp controlinfo.h controlinfo.ui
        docuwindow.cpp docuwindow.h
        invokemethod.cpp invokemethod.h invokemethod.ui
        main.cpp
        mainwindow.cpp mainwindow.h mainwindow.ui
    PUBLIC_LIBRARIES
        Qt::AxContainer
        Qt::AxContainerPrivate
        Qt::AxServer
        Qt::Gui
        Qt::PrintSupport
        Qt::Widgets
    ENABLE_AUTOGEN_TOOLS
        uic
)

# Resources:
set(testcon_resource_files
    "images/controlmethods.png"
    "images/controlproperties.png"
    "images/filenew.png"
)

qt_internal_add_resource(testcon "testcon" # special case
    PREFIX
        "/"
    FILES
        ${testcon_resource_files}
)


#### Keys ignored in scope 1:.:.:testcon.pro:<TRUE>:
# RC_FILE = "testcon.rc"
# TEMPLATE = "app"

## Scopes:
#####################################################################

#### Keys ignored in scope 2:.:.:testcon.pro:NOT MINGW:
# QMAKE_POST_LINK = "midl" "$$shell_quote($$shell_path $$PWD/testcon.idl)" "&&" "move" "testcon.tlb" "$(TARGETDIR)"
