%modules = ( # path to module name map
    "ActiveQt" => "$basedir/src/activeqt",
);
%moduleheaders = ( # restrict the module headers to those found in relative path
);
%classnames = (
);
%mastercontent = (
    "gui" => "#include <QtGui/QtGui>\n",
);
%modulepris = (
    "ActiveQt" => "$basedir/modules/qt_activeqt.pri",
);
