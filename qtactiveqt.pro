TEMPLATE = subdirs

activeqt_src.subdir = src
activeqt_src.target = sub-src

activeqt_tests.subdir = tests
activeqt_tests.target = sub-tests
activeqt_tests.depends = activeqt_src
activeqt_tests.CONFIG = no_default_install
!contains(QT_BUILD_PARTS,tests):activeqt_tests.CONFIG += no_default_target

activeqt_tools.subdir = tools
activeqt_tools.target = sub-tools
activeqt_tools.depends = activeqt_src

activeqt_examples.subdir = examples
activeqt_examples.target = sub-examples
activeqt_examples.depends = activeqt_src

win32 {
    SUBDIRS = activeqt_src \
              activeqt_tests \
              activeqt_tools \
              activeqt_examples
}
else {
    message("ActiveQt is a Windows-only module - will not be built")
}
