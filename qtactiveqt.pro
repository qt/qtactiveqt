CONFIG += tests_need_tools
load(qt_parts)

!win32 {
    message("ActiveQt is a Windows-only module. Will just generate a docs target.")
    SUBDIRS = src
}
