# Generated from dumpcpp.pro.

#####################################################################
## dumpcpp Tool:
#####################################################################

qt_add_tool(dumpcpp
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

#### Keys ignored in scope 1:.:.:dumpcpp.pro:<TRUE>:
# QMAKE_TARGET_DESCRIPTION = "Active Qt DumpCpp"
