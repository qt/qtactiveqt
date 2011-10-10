TEMPLATE = subdirs

CONFIG	+= ordered
CONFIG += module
SUBDIRS	= container
MODULE_PRI = ../../modules/qt_activeqt.pri
!wince*: SUBDIRS += control
