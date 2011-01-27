QT_DECLARATIVE_VERSION = $$QT_VERSION
QT_DECLARATIVE_MAJOR_VERSION = $$QT_MAJOR_VERSION
QT_DECLARATIVE_MINOR_VERSION = $$QT_MINOR_VERSION
QT_DECLARATIVE_PATCH_VERSION = $$QT_PATCH_VERSION

QT.activeqt.name = ActiveQt
QT.activeqt.bins = $$QT_MODULE_BIN_BASE
QT.activeqt.includes = $$QT_MODULE_INCLUDE_BASE $$QT_MODULE_INCLUDE_BASE/ActiveQt
QT.activeqt.private_includes = $$QT_MODULE_INCLUDE_BASE/ActiveQt/private
QT.activeqt.sources = $$QT_MODULE_BASE/src/activeqt
QT.activeqt.libs = $$QT_MODULE_LIB_BASE
QT.activeqt.depends = gui
QT.activeqt.DEFINES = QT_ACTIVEQT_LIB

QT_CONFIG += activeqt
