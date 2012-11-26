TEMPLATE = app
TARGET	 = openglax

CONFIG += qt warn_off
QT += widgets axserver opengl

HEADERS	 = glbox.h \
	   globjwin.h
SOURCES	 = glbox.cpp \
	   globjwin.cpp \
	   main.cpp

RC_FILE = opengl.rc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/activeqt/opengl
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS $$RC_FILE opengl.ico opengl.pro
sources.path = $$[QT_INSTALL_EXAMPLES]/activeqt/opengl
INSTALLS += target sources
