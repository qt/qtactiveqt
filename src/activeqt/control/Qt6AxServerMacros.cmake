# Adds an ActiveX server executable, generates an IDL file and links the produced .tbl to the
# executable.
# Arguments: See qt6_target_idl
#
# This function is currently in Technical Preview.
# Its signature and behavior might change.
function(qt6_add_axserver_executable target)
    cmake_parse_arguments(arg "SKIP_AX_SERVER_REGISTRATION" "" "" ${ARGN})
    if(arg_SKIP_AX_SERVER_REGISTRATION)
        set(arg_SKIP_AX_SERVER_REGISTRATION "SKIP_AX_SERVER_REGISTRATION")
    else()
        unset(arg_SKIP_AX_SERVER_REGISTRATION)
    endif()
    qt_add_executable(${target} ${arg_UNPARSED_ARGUMENTS})
    set_target_properties(${target} PROPERTIES WIN32_EXECUTABLE TRUE)
    target_link_libraries(${target} PRIVATE ${QT_CMAKE_EXPORT_NAMESPACE}::AxServer)
    if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.19)
        # Need to wrap in an EVAL CODE or else ${target} won't be evaluated
        # due to special behavior of cmake_language() argument handling
        cmake_language(EVAL CODE
            "cmake_language(DEFER CALL qt6_target_idl ${target} ${arg_SKIP_AX_SERVER_REGISTRATION})"
        )
    else()
        qt6_target_idl(${target} ${arg_SKIP_AX_SERVER_REGISTRATION})
    endif()
endfunction()

# Adds an ActiveX server library, generates an IDL file and links the produced .tbl to the
# dll.
# Arguments: See qt6_target_idl
#
# This function is currently in Technical Preview.
# Its signature and behavior might change.
function(qt6_add_axserver_library target)
    cmake_parse_arguments(arg "SKIP_AX_SERVER_REGISTRATION" "" "" ${ARGN})
    if(arg_SKIP_AX_SERVER_REGISTRATION)
        set(arg_SKIP_AX_SERVER_REGISTRATION "SKIP_AX_SERVER_REGISTRATION")
    else()
        unset(arg_SKIP_AX_SERVER_REGISTRATION)
    endif()
    add_library(${target} SHARED ${arg_UNPARSED_ARGUMENTS})
    target_link_libraries(${target} PRIVATE ${QT_CMAKE_EXPORT_NAMESPACE}::AxServer)
    if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.19)
        # Need to wrap in an EVAL CODE or else ${target} won't be evaluated
        # due to special behavior of cmake_language() argument handling
        cmake_language(EVAL CODE
            "cmake_language(DEFER CALL qt6_target_idl ${target} ${arg_SKIP_AX_SERVER_REGISTRATION})"
        )
    else()
        qt6_target_idl(${target} ${arg_SKIP_AX_SERVER_REGISTRATION})
    endif()
endfunction()

# Adds post-build rules to generate and link IDC/MIDL artifacts to the library or executable.
# Arguments:
#   SKIP_AX_SERVER_REGISTRATION skips the ActiveX server registration.
#      Note: You may also use the QT_SKIP_AX_SERVER_REGISTRATION variable to globally skip
#      the ActiveX server registrations.
#
# This function is currently in Technical Preview.
# Its signature and behavior might change.
function(qt6_target_idl target)
    cmake_parse_arguments(arg "SKIP_AX_SERVER_REGISTRATION" "" "" ${ARGN})
    if(NOT WIN32)
        return()
    endif()

    set(output_idl "${CMAKE_CURRENT_BINARY_DIR}/${target}$<CONFIG>.idl")
    set(output_tlb "${CMAKE_CURRENT_BINARY_DIR}/${target}$<CONFIG>.tlb")

    set(tlb_command_list "")
    list(APPEND tlb_command_list ${QT_TOOL_PATH_SETUP_COMMAND})
    list(APPEND tlb_command_list COMMAND ${QT_CMAKE_EXPORT_NAMESPACE}::idc
        "$<TARGET_FILE:${target}>" /idl "${output_idl}" -version 1.0
    )
    list(APPEND tlb_command_list COMMAND midl "${output_idl}" /nologo /tlb "${output_tlb}")

    get_target_property(sources ${target} "SOURCES")
    set(has_rc FALSE)
    foreach(src IN LISTS sources)
        if(src MATCHES ".*\\.rc$")
            set(has_rc TRUE)
            break()
        endif()
    endforeach()
    if(has_rc)
        list(APPEND tlb_command_list COMMAND ${QT_CMAKE_EXPORT_NAMESPACE}::idc
            "$<TARGET_FILE:${target}>" /tlb "${output_tlb}"
        )
    else()
        message(AUTHOR_WARNING "No rc-file linked into project. The type library of the ${target} \
target will be a separate file."
        )
        # TODO: Perhaps it makes sense to add an installation rule that delivers the generated .tlb
        # file as a part of the development package.
    endif()

    if(NOT arg_SKIP_AX_SERVER_REGISTRATION AND NOT QT_SKIP_AX_SERVER_REGISTRATION)
        list(APPEND tlb_command_list COMMAND ${QT_CMAKE_EXPORT_NAMESPACE}::idc
            "$<TARGET_FILE:${target}>" /regserver
        )
    endif()
    add_custom_command(TARGET ${target} POST_BUILD
        ${tlb_command_list}
        DEPENDS
            ${QT_CMAKE_EXPORT_NAMESPACE}::idc
        VERBATIM
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
