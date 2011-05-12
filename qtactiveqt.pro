TEMPLATE = subdirs

activeqt_src.subdir = $$IN_PWD/src
activeqt_src.target = sub-src

activeqt_tools.subdir = $$IN_PWD/tools
activeqt_tools.target = sub-tools
activeqt_tools.depends = activeqt_src

activeqt_examples.subdir = $$IN_PWD/examples
activeqt_examples.target = sub-examples
activeqt_examples.depends = activeqt_src

win32 {
    SUBDIRS = activeqt_src \
              activeqt_tools \
              activeqt_examples
}
else {
    message("ActiveQt is a Windows-only module - will not be built")
}
