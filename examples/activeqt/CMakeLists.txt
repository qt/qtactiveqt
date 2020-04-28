# Generated from activeqt.pro.

add_subdirectory(comapp)
add_subdirectory(hierarchy)
add_subdirectory(menus)
add_subdirectory(multiple)
add_subdirectory(simple)
add_subdirectory(wrapper)
if(MINGW OR QT_BUILD_SHARED_LIBS)
    add_subdirectory(mediaplayer)
endif()
if(TARGET Qt6::OpenGLWidgets AND QT_FEATURE_opengl AND NOT QT_FEATURE_opengles2) # special case
    add_subdirectory(opengl)
endif()
if(TARGET Qt::QuickControls2)
    add_subdirectory(simpleqml)
endif()
