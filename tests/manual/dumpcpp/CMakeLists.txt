# Generated from dumpcpp.pro.

#####################################################################
## dumpcpp Binary:
#####################################################################

qt_internal_add_manual_test(tst_dumpcpp_manual # special case
    SOURCES
        ../shared/metaobjectdump.cpp ../shared/metaobjectdump.h
        ../shared/textdialog.cpp ../shared/textdialog.h
        main.cpp
    INCLUDE_DIRECTORIES
        ../shared
    PUBLIC_LIBRARIES
        Qt::AxContainer
        Qt::Gui
        Qt::Test
        Qt::Widgets
)

#### Keys ignored in scope 1:.:.:dumpcpp.pro:<TRUE>:
# TEMPLATE = "app"
# TYPELIBS = "$$(SystemRoot)\\system32\\ieframe.dll"

qt6_target_typelibs(tst_dumpcpp_manual LIBRARIES "ieframe.dll") # special case

## Scopes:
#####################################################################
