# This modules provides the header files, installed under "ActiveQt/".
# It also contains shared code that is used by axcontainer and axserver.

TARGET = ActiveQt
CONFIG += static
QT += gui-private

HEADERS = \
    shared/qaxtypefunctions_p.h \
    shared/qaxutils_p.h

SOURCES = \
    shared/qaxtypefunctions.cpp \
    shared/qaxutils.cpp

MODULE = axbase
load(qt_module)
DLLDESTDIR =
VERSION =
