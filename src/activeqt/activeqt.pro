TEMPLATE = subdirs

CONFIG	+= ordered
SUBDIRS	= container
!wince*: SUBDIRS += control

TARGET = ActiveQt
VERSION = $$QT_VERSION
MODULE = activeqt
MODULE_DEPENDS = widgets
MODULE_PRI = $$section(PWD, /, 0, -3)/modules/qt_activeqt.pri
load(qt_module_fwdpri)
load(qt_module_headers)
load(qt_installs)
