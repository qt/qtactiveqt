TEMPLATE = subdirs
SUBDIRS += \
    qaxobject \
    qaxscript \
    dumpcpp \
    cmake

*g++*: SUBDIRS -= \
    qaxscript \
