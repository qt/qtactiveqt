load(qt_parts)

# Autotests require tools
sub_tests.depends += sub_tools

!win32 {
    message("ActiveQt is a Windows-only module - will not be built")
    SUBDIRS =
}
