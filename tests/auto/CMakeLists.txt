# Generated from auto.pro.

add_subdirectory(conversion)
add_subdirectory(qaxobject)
add_subdirectory(dumpcpp)
add_subdirectory(cmake)
if(NOT GCC)
    add_subdirectory(qaxscript)
endif()
