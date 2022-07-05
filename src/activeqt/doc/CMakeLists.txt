# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

# special case skip regeneration

add_library(ActiveQt INTERFACE)
target_link_libraries(ActiveQt INTERFACE Qt::Core)
qt_internal_add_docs(ActiveQt activeqt.qdocconf)
