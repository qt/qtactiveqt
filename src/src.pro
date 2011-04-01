TEMPLATE = subdirs

subdir_activeqt.subdir = $$IN_PWD/activeqt
subdir_activeqt.target = sub_activeqt

SUBDIRS += subdir_activeqt

CONFIG += module
MODULE_PRI = ../modules/qt_activeqt.pri
