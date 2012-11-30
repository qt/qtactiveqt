CONFIG += tests_need_tools
load(qt_parts)

!win32 {
    message("ActiveQt is a Windows-only module - will not be built")
    SUBDIRS =
}
