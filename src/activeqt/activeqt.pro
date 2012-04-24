TEMPLATE = subdirs

CONFIG	+= ordered
SUBDIRS	= container
!wince*: SUBDIRS += control

TARGET = ActiveQt
MODULE = activeqt
MODULE_DEPENDS = widgets
MODULE_PRI = $$section(PWD, /, 0, -3)/modules/qt_activeqt.pri
VERSION = $$QT_VERSION
mod_base = $$section(PWD, /, 0, -3)
mod_out_base = $$section(OUT_PWD, /, 0, -3)
load(qt_module_fwdpri)
load(qt_module_headers)
load(qt_installs)
