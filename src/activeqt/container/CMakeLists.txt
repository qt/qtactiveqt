# Generated from container.pro.

#####################################################################
## AxContainer Module:
#####################################################################

qt_internal_add_module(AxContainer # special case
    STATIC
    QMAKE_MODULE_CONFIG dumpcpp
    SOURCES
        ../control/qaxaggregated.h
        ../shared/qaxtypes.cpp ../shared/qaxtypes_p.h
        qaxbase.cpp qaxbase.h qaxbase_p.h
        qaxdump.cpp
        qaxobject.cpp qaxobject.h qaxobject_p.h
        qaxobjectinterface.h
        qaxscript.cpp qaxscript.h
        qaxscriptwrapper.cpp
        qaxselect.cpp qaxselect.h qaxselect.ui
        qaxwidget.cpp qaxwidget.h qaxwidget_p.h
    LIBRARIES
        Qt::AxBasePrivate
        Qt::CorePrivate
        Qt::GuiPrivate
        Qt::WidgetsPrivate
    PUBLIC_LIBRARIES
        Qt::Core
        Qt::Gui
        Qt::Widgets
    ENABLE_AUTOGEN_TOOLS
        uic
)

#### Keys ignored in scope 1:.:.:container.pro:<TRUE>:
# MODULE = "axcontainer"
# MODULE_CONFIG = "dumpcpp"
