# Generated from idc.pro.

#####################################################################
## idc Tool:
#####################################################################

qt_get_tool_target_name(target_name idc)
qt_internal_add_tool(${target_name} # special case
#    BOOTSTRAP # special case
    TARGET_DESCRIPTION "Active Qt Interface Description Compiler"
    TOOLS_TARGET AxServer # special case
    SOURCES
        main.cpp
)
qt_internal_return_unless_building_tools()

#### Keys ignored in scope 1:.:.:idc.pro:<TRUE>:
# QMAKE_TARGET_DESCRIPTION = "Active Qt Interface Description Compiler"
# _OPTION = "host_build"
