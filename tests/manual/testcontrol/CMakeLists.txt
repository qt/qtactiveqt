# Generated from testcontrol.pro.

#####################################################################
## testcontrol Binary:
#####################################################################

qt_internal_add_manual_test(tst_testcontrol_manual # special case
    GUI
    SOURCES
        main.cpp
        testcontrol.rc
    PUBLIC_LIBRARIES
        Qt::AxServer
        Qt::Gui
        Qt::Widgets
)
qt_disable_warnings(tst_testcontrol_manual)
qt6_target_idl(tst_testcontrol_manual)

#### Keys ignored in scope 1:.:.:testcontrol.pro:<TRUE>:
# RC_FILE = "testcontrol.rc"
# TEMPLATE = "app"
