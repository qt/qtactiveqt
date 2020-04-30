win32:!winrt {
    TEMPLATE = subdirs

    CONFIG += ordered
    activeqt.file = activeqt.prx
    SUBDIRS = axbase control container activeqt
} else {
    # fake project for creating the documentation
    message("ActiveQt is a Windows Desktop-only module. Will just generate a docs target.")
    TEMPLATE = aux
    CONFIG += force_qt
    QMAKE_DOCS = $$PWD/doc/activeqt.qdocconf
}

