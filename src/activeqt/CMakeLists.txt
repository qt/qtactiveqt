# Generated from activeqt.pro.

# special case begin
add_subdirectory(axbase)
add_subdirectory(control)
add_subdirectory(container)

qt_internal_add_module(ActiveQt HEADER_MODULE MODULE_INCLUDE_NAME ActiveQt)
qt_internal_add_docs(ActiveQt
    doc/activeqt.qdocconf
)
# special case end
## Scopes:
#####################################################################

#### Keys ignored in scope 2:.:.:activeqt.pro:WIN32:
# SUBDIRS = "axbase" "control" "container" "activeqt"
# TEMPLATE = "subdirs"
# activeqt.file = "activeqt.prx"

#### Keys ignored in scope 3:.:.:activeqt.pro:else:
# TEMPLATE = "aux"
