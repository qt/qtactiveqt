QT.activeqt.VERSION = 5.0.0
QT.activeqt.MAJOR_VERSION = 5
QT.activeqt.MINOR_VERSION = 0
QT.activeqt.PATCH_VERSION = 0

QT.activeqt.name = ActiveQt
QT.activeqt.bins = $$QT_MODULE_BIN_BASE
QT.activeqt.includes = $$QT_MODULE_INCLUDE_BASE $$QT_MODULE_INCLUDE_BASE/ActiveQt
QT.activeqt.private_includes = $$QT_MODULE_INCLUDE_BASE/ActiveQt/$$QT.activeqt.VERSION $$QT_MODULE_INCLUDE_BASE/ActiveQt/$$QT.activeqt.VERSION/ActiveQt
QT.activeqt.sources = $$QT_MODULE_BASE/src/activeqt
QT.activeqt.libs = $$QT_MODULE_LIB_BASE
QT.activeqt.plugins = $$QT_MODULE_PLUGIN_BASE
QT.activeqt.imports = $$QT_MODULE_IMPORT_BASE
QT.activeqt.depends = gui
QT.activeqt.DEFINES = QT_ACTIVEQT_LIB

QT_CONFIG += activeqt
