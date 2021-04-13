# Generated from control.pro.

#####################################################################
## AxServer Module:
#####################################################################

qt_internal_add_module(AxServer # special case
    STATIC
    QMAKE_MODULE_CONFIG idcidl force_import_plugins
    SOURCES
        ../shared/qaxtypes.cpp ../shared/qaxtypes_p.h
        qaxaggregated.cpp qaxaggregated.h
        qaxbindable.cpp qaxbindable.h
        qaxfactory.cpp qaxfactory.h
        qaxmain.cpp
        qaxserver.cpp
        qaxserverbase.cpp
        qaxserverdll.cpp
        qaxservermain.cpp
        qclassfactory_p.h
    DEFINES
        QAX_SERVER
    PUBLIC_DEFINES
        QAXSERVER
    LIBRARIES
        Qt::AxBasePrivate
        Qt::CorePrivate
        Qt::GuiPrivate
        Qt::WidgetsPrivate
    PUBLIC_LIBRARIES
        Qt::Core
        Qt::Gui
        Qt::Widgets
        shell32
)

#### Keys ignored in scope 1:.:.:control.pro:<TRUE>:
# MODULE = "axserver"
# MODULE_CONFIG = "idcidl" "force_import_plugins"

## Scopes:
#####################################################################

qt_internal_extend_target(AxServer CONDITION MINGW
    DEFINES
        QT_NEEDS_QMAIN
)
