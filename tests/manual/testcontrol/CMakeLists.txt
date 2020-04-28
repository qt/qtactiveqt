# Generated from testcontrol.pro.

#####################################################################
## testcontrol Binary:
#####################################################################

qt_add_executable(testcontrol
    GUI
    SOURCES
        main.cpp
    PUBLIC_LIBRARIES
        Qt::AxServer
        Qt::Gui
        Qt::Widgets
)
qt_disable_warnings(testcontrol)

#### Keys ignored in scope 1:.:.:testcontrol.pro:<TRUE>:
# RC_FILE = "testcontrol.rc"
# TEMPLATE = "app"
