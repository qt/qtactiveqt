#############################################################################
##
## Copyright (C) 2022 The Qt Company Ltd.
## Contact: https://www.qt.io/licensing/
##
## This file is part of the ActiveQt module of the Qt Toolkit.
##
## $QT_BEGIN_LICENSE:COMM$
##
## Commercial License Usage
## Licensees holding valid commercial Qt licenses may use this file in
## accordance with the commercial license agreement provided with the
## Software or, alternatively, in accordance with the terms contained in
## a written agreement between you and The Qt Company. For licensing terms
## and conditions see https://www.qt.io/terms-conditions. For further
## information use the contact form at https://www.qt.io/contact-us.
##
## $QT_END_LICENSE$
##
##
##
##
##
##
##
##
##############################################################################

sub QAxWidget2_Click {
    $QAxWidget2->{'lineWidth'} = $QAxWidget2->{'lineWidth'} + 1;
    $MainWindow->logMacro(0, "Hello from Perl: QAxWidget2_Click", 0, "");
}

sub fatLines
{
    $QAxWidget2->{'lineWidth'} = 25;
}

sub thinLines
{
    $QAxWidget2->{'lineWidth'} = 1;
}

sub setLineWidth(width)
{
    $QAxWidget2->{'lineWidth'} = width;
}

sub getLineWidth()
{
    return $QAxWidget2->{'lineWidth'};
}
