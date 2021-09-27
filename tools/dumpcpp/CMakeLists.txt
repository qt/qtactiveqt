# Generated from dumpcpp.pro.

#####################################################################
## dumpcpp Tool:
#####################################################################

qt_get_tool_target_name(target_name dumpcpp)
qt_internal_add_tool(${target_name} # special case
    TARGET_DESCRIPTION "Active Qt DumpCpp"
    TOOLS_TARGET AxContainer # special case
    SOURCES
        main.cpp
        moc.cpp moc.h
    DEFINES
        QT_ASCII_CAST_WARNINGS
        QT_NO_CAST_TO_ASCII
    PUBLIC_LIBRARIES
        Qt::AxContainer
        Qt::CorePrivate
        Qt::Gui
        Qt::Widgets
)
qt_internal_return_unless_building_tools()

#### Keys ignored in scope 1:.:.:dumpcpp.pro:<TRUE>:
# QMAKE_TARGET_DESCRIPTION = "Active Qt DumpCpp"
