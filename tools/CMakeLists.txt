# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial

qt_exclude_tool_directories_from_default_target(
    testcon
)

add_subdirectory(dumpdoc)
add_subdirectory(dumpcpp)
add_subdirectory(testcon)
