TEMPLATE = app
TARGET	 = openglax

CONFIG	+= qt warn_off qaxserver

QT += widgets opengl

HEADERS	 = glbox.h \
	   globjwin.h
SOURCES	 = glbox.cpp \
	   globjwin.cpp \
	   main.cpp

RC_FILE = opengl.rc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/activeqt/opengl
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS $$RC_FILE qaxserver.ico opengl.pro
sources.path = $$[QT_INSTALL_EXAMPLES]/activeqt/opengl
INSTALLS += target sources
