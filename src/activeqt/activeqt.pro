TEMPLATE = subdirs

CONFIG	+= ordered
SUBDIRS	= container
!wince*: SUBDIRS += control

TARGET = ActiveQt
MODULE = activeqt
MODULE_DEPENDS = widgets
MODULE_PRI = $$section(PWD, /, 0, -3)/modules/qt_activeqt.pri
MODULE_BASE_DIR = $$section(PWD, /, 0, -3)
MODULE_BASE_OUTDIR = $$section(OUT_PWD, /, 0, -3)
MODULE_PROFILE_DIR = $$MODULE_BASE_DIR
MODULE_QMAKE_OUTDIR = $$MODULE_BASE_OUTDIR
load(qt_module_fwdpri)
load(qt_module_headers)
load(qt_installs)
