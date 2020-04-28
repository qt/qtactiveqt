# Generated from auto.pro.

add_subdirectory(conversion)
add_subdirectory(qaxobject)
# add_subdirectory(dumpcpp) (needs typelib target) # special case
#add_subdirectory(cmake) # special case
if(NOT GCC)
    add_subdirectory(qaxscript)
endif()
