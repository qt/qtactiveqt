# Generated from axbase.pro.

#####################################################################
## AxBase Module:
#####################################################################

qt_internal_add_module(AxBase # special case
    STATIC
    INTERNAL_MODULE
    SOURCES
        qaxtypefunctions.cpp qaxtypefunctions_p.h
        qaxutils.cpp qaxutils_p.h
    LIBRARIES
        advapi32
        gdi32
        ole32
        oleaut32
        user32
    PUBLIC_LIBRARIES
        Qt::Core
        Qt::CorePrivate
        Qt::Gui
        Qt::GuiPrivate
        Qt::Widgets
)

#### Keys ignored in scope 1:.:.:axbase.pro:<TRUE>:
# MODULE = "axbase"

## Scopes:
#####################################################################

qt_extend_target(AxBase CONDITION MINGW
    LIBRARIES
        uuid
)
