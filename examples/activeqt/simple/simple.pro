TEMPLATE = app
TARGET	 = simpleax

CONFIG	+= qt warn_off qaxserver
QT += widgets

SOURCES	 = main.cpp
RC_FILE	 = $$QT.activeqt.sources/control/qaxserver.rc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/activeqt/simple
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS simple.pro
sources.path = $$[QT_INSTALL_EXAMPLES]/activeqt/simple
INSTALLS += target sources
