# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

# Generated from activeqt.pro.

# special case begin
add_subdirectory(axbase)
add_subdirectory(control)
add_subdirectory(container)

# We disable this headersclean check this way, since syncqt adds the header files from the
# subdirectories to the ActiveQt module. This triggers the headersclean rules creation and
# execution, but they fail because ActiveQt module doesn't link the necessary libraries so
# their compile flags and include directories are missing.
# We cannot simply link libraries because the missing include directories belong to the
# AxServer and AxContainer modules which have conflicting object files and cannot be linked in the
# same time.
set(QT_FEATURE_headersclean_BACKUP "${QT_FEATURE_headersclean}")
set(QT_FEATURE_headersclean OFF)
qt_internal_add_module(ActiveQt HEADER_MODULE MODULE_INCLUDE_NAME ActiveQt)
qt_internal_add_docs(ActiveQt
    doc/activeqt.qdocconf
)
set(QT_FEATURE_headersclean "${QT_FEATURE_headersclean_BACKUP}")

# special case end
## Scopes:
#####################################################################

#### Keys ignored in scope 2:.:.:activeqt.pro:WIN32:
# SUBDIRS = "axbase" "control" "container" "activeqt"
# TEMPLATE = "subdirs"
# activeqt.file = "activeqt.prx"

#### Keys ignored in scope 3:.:.:activeqt.pro:else:
# TEMPLATE = "aux"
