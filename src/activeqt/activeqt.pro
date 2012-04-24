TEMPLATE = subdirs

CONFIG += qt_install_module qt_installs
MODULE_PRI = $$section(PWD, /, 0, -3)/modules/qt_activeqt.pri

CONFIG	+= ordered
SUBDIRS	= container
!wince*: SUBDIRS += control
