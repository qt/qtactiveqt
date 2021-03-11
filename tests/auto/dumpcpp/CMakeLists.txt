# Generated from dumpcpp.pro.

#####################################################################
## tst_dumpcpp Test:
#####################################################################

qt_internal_add_test(tst_dumpcpp
    SOURCES
        tst_dumpcpp.cpp
    PUBLIC_LIBRARIES
        Qt::AxContainer
        Qt::Gui
        Qt::Widgets
)

#### Keys ignored in scope 1:.:.:dumpcpp.pro:<TRUE>:
# TYPELIBS = "$$(SystemRoot)\\system32\\ieframe.dll"

qt6_target_typelibs(tst_dumpcpp LIBRARIES "ieframe.dll") # special case

## Scopes:
#####################################################################
