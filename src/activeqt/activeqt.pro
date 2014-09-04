win32:!winrt {
    TEMPLATE = subdirs

    CONFIG += ordered
    axshared.file = axshared.prx
    SUBDIRS = axshared container control
} else {
    # fake project for creating the documentation
    TEMPLATE = aux
    QMAKE_DOCS = $$PWD/doc/activeqt.qdocconf
}

