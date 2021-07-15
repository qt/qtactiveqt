# Adds an ActiveX server executable, generates an IDL file and links the produced .tbl to the
# executable.
# Arguments: See qt6_target_idl
#
# This function is currently in Technical Preview.
# Its signature and behavior might change.
function(qt6_add_axserver_executable target)
    cmake_parse_arguments(arg "NO_AX_SERVER_REGISTRATION" "" "" ${ARGN})
    if(arg_NO_AX_SERVER_REGISTRATION)
        set(arg_NO_AX_SERVER_REGISTRATION "NO_AX_SERVER_REGISTRATION")
    else()
        unset(arg_NO_AX_SERVER_REGISTRATION)
    endif()
    qt_add_executable(${target} ${arg_UNPARSED_ARGUMENTS})
    set_target_properties(${target} PROPERTIES WIN32_EXECUTABLE TRUE)
    target_link_libraries(${target} PRIVATE ${QT_CMAKE_EXPORT_NAMESPACE}::AxServer)
    qt6_target_idl(${target} ${arg_NO_AX_SERVER_REGISTRATION})
endfunction()

# Adds an ActiveX server library, generates an IDL file and links the produced .tbl to the
# dll.
# Arguments: See qt6_target_idl
#
# This function is currently in Technical Preview.
# Its signature and behavior might change.
function(qt6_add_axserver_library target)
    cmake_parse_arguments(arg "NO_AX_SERVER_REGISTRATION" "" "" ${ARGN})
    if(arg_NO_AX_SERVER_REGISTRATION)
        set(arg_NO_AX_SERVER_REGISTRATION "NO_AX_SERVER_REGISTRATION")
    else()
        unset(arg_NO_AX_SERVER_REGISTRATION)
    endif()
    add_library(${target} SHARED ${arg_UNPARSED_ARGUMENTS})
    target_link_libraries(${target} PRIVATE ${QT_CMAKE_EXPORT_NAMESPACE}::AxServer)
    qt6_target_idl(${target} ${arg_NO_AX_SERVER_REGISTRATION})
endfunction()

# Adds post-build rules to generate and link IDC/MIDL artifacts to the library or executable.
# Arguments:
#   NO_AX_SERVER_REGISTRATION skips the ActiveX server registration.
#      Note: You may also use the QT_NO_AX_SERVER_REGISTRATION variable to globally skip
#      the ActiveX server registrations.
#
# This function is currently in Technical Preview.
# Its signature and behavior might change.
function(qt6_target_idl target)
    cmake_parse_arguments(arg "NO_AX_SERVER_REGISTRATION" "" "" ${ARGN})
    if(NOT WIN32)
        return()
    endif()

    set(output_idl "${CMAKE_CURRENT_BINARY_DIR}/${target}$<CONFIG>.idl")
    set(output_tlb "${CMAKE_CURRENT_BINARY_DIR}/${target}$<CONFIG>.tlb")

    set(tlb_command_list "")
    _qt_internal_wrap_tool_command(tlb_command_list APPEND
        "$<TARGET_FILE:${QT_CMAKE_EXPORT_NAMESPACE}::idc>" "$<TARGET_FILE:${target}>"
        /idl "${output_idl}" -version 1.0
    )

    _qt_internal_wrap_tool_command(tlb_command_list APPEND
        midl "${output_idl}" /nologo /tlb "${output_tlb}"
    )

    set(rc_files "$<FILTER:$<TARGET_PROPERTY:${target},SOURCES>,INCLUDE,\\.rc$>")
    set(have_rc_files "$<NOT:$<BOOL:$<STREQUAL:${rc_files},>>>")
    set(rc_cmd "$<TARGET_FILE:${QT_CMAKE_EXPORT_NAMESPACE}::idc>$<SEMICOLON>\
$<TARGET_FILE:${target}>$<SEMICOLON>/tlb$<SEMICOLON>${output_tlb}")
    set(no_rc_cmd "echo \"No rc-file linked into project. The type library of the ${target} \
target will be a separate file.\"")
    _qt_internal_wrap_tool_command(tlb_command_list APPEND
        "$<IF:${have_rc_files},${rc_cmd},${no_rc_cmd}>"
    )

    if(NOT arg_NO_AX_SERVER_REGISTRATION AND NOT QT_NO_AX_SERVER_REGISTRATION)
        _qt_internal_wrap_tool_command(tlb_command_list APPEND
            "$<TARGET_FILE:${QT_CMAKE_EXPORT_NAMESPACE}::idc>"
             "$<TARGET_FILE:${target}>" /regserver
        )
    endif()
    add_custom_command(TARGET ${target} POST_BUILD
        ${tlb_command_list}
        DEPENDS
            ${QT_CMAKE_EXPORT_NAMESPACE}::idc
        VERBATIM
        COMMAND_EXPAND_LISTS
    )
endfunction()

if(NOT QT_NO_CREATE_VERSIONLESS_FUNCTIONS)
    function(qt_add_axserver_executable)
        qt6_add_axserver_executable(${ARGV})
    endfunction()
    function(qt_add_axserver_library)
        qt6_add_axserver_library(${ARGV})
    endfunction()
    function(qt_target_idl)
        qt6_target_idl(${ARGV})
    endfunction()
endif()
