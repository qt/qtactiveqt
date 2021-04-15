# special case skip regeneration

add_library(ActiveQt INTERFACE)
target_link_libraries(ActiveQt INTERFACE Qt::Core)
qt_internal_add_docs(ActiveQt activeqt.qdocconf)
