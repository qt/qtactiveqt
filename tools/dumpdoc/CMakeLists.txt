# Generated from dumpdoc.pro.

#####################################################################
## dumpdoc Tool:
#####################################################################

qt_get_tool_target_name(target_name dumpdoc)
qt_internal_add_tool(${target_name} # special case
    TARGET_DESCRIPTION "Active Qt DumpDoc"
    TOOLS_TARGET AxContainer # special case
    SOURCES
        main.cpp
    PUBLIC_LIBRARIES
        Qt::AxContainer
        Qt::Gui
        Qt::Widgets
)
qt_internal_return_unless_building_tools()

#### Keys ignored in scope 1:.:.:dumpdoc.pro:<TRUE>:
# QMAKE_TARGET_DESCRIPTION = "Active Qt DumpDoc"
