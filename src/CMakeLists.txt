# Generated from src.pro.

add_subdirectory(activeqt)
if(WIN32 AND NOT WINRT)
    add_subdirectory(tools)
endif()
