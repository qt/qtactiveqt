CONFIG += testcase qaxcontainer
QT += widgets testlib
SOURCES += tst_dumpcpp.cpp
TARGET = tst_dumpcpp

# Assume Web Browser type library is available in all windows installations
TYPELIBS = $$system(dumpcpp -getfile {EAB22AC0-30C1-11CF-A7EB-0000C05BAE0B})

isEmpty(TYPELIBS) {
    message("Web Browser type library for test not found!")
}