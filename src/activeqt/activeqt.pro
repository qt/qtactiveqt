win32 {
    TEMPLATE = subdirs

    CONFIG	+= ordered
    axshared.file = axshared.prx
    SUBDIRS = axshared container
    !wince: SUBDIRS += control
} else {
    TEMPLATE = aux
    QMAKE_DOCS = $$PWD/doc/activeqt.qdocconf
}

