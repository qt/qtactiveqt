/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the test suite of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL-EXCEPT$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <ActiveQt/QAxSelect>
#include <ActiveQt/QAxWidget>

#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>

#include <QtGui/QFontDatabase>
#include <QtGui/QScreen>

#include <QtCore/QCommandLineOption>
#include <QtCore/QCommandLineParser>
#include <QtCore/QDebug>
#include <QtCore/QMetaMethod>
#include <QtCore/QMetaObject>
#include <QtCore/QPair>
#include <QtCore/QStringList>
#include <QtCore/QSysInfo>

#ifdef QT_DIAG_LIB
#  include <qwidgetdump.h>
#  include <nativewindowdump.h>
#  include <qwindowdump.h>
#endif

#include <algorithm>
#include <iterator>

QT_USE_NAMESPACE

static inline bool isOptionSet(int argc, char *argv[], const char *option)
{
    return (argv + argc) !=
        std::find_if(argv + 1, argv + argc,
                     [option] (const char *arg) { return !qstrcmp(arg, option); });
}

using rightAlignNumber = QPair<int, int>; // Use as str << rightAlignNumber(value, width)

QTextStream &operator<<(QTextStream &str, const rightAlignNumber &r)
{
    auto oldWidth = str.fieldWidth();
    str.setFieldWidth(r.second);
    auto oldAlignment = str.fieldAlignment();
    str.setFieldAlignment(QTextStream::AlignRight);
    str << r.first;
    str.setFieldAlignment(oldAlignment);
    str.setFieldWidth(oldWidth);
    return str;
}

QTextStream &operator<<(QTextStream &str, const QMetaEnum &me)
{
    const int keyCount = me.keyCount();
    str << me.name() << ' ' << keyCount << " keys";
    if (me.isFlag())
        str << " [flag]";
    if (me.isScoped())
        str << " [scoped]";
    const int maxLogCount = std::min(6, keyCount);
    str << " {";
    for (int k = 0; k < maxLogCount; ++k) {
        if (k)
            str << ", ";
        str << me.key(k) << " = " << me.value(k);
    }
    if (maxLogCount < keyCount)
        str << ",...";
    str << '}';
    return str;
}

QTextStream &operator<<(QTextStream &str, const QMetaClassInfo &mc)
{
    str << '"' << mc.name() << "\": \"" << mc.value() << '"';
    return str;
}

QTextStream &operator<<(QTextStream &str, const QMetaProperty &mp)
{
    str << mp.typeName() << ' ' << mp.name();
    if (mp.isWritable())
        str << " [writable]";
    if (mp.isResettable())
        str << " [resettable]";
    if (mp.isDesignable())
        str << " [designable]";
    if (mp.isStored())
        str << " [stored]";
    if (mp.isUser())
        str << " [user]";
    if (mp.isConstant())
        str << " [constant]";
     if (mp.isFinal())
         str << " [final]";
     if (mp.isRequired())
         str << " [required]";
     if (mp.isFlagType())
         str << " [flag]";
     if (mp.isEnumType())
         str << " [enum " << mp.enumerator().name() << ']';
     if (mp.hasNotifySignal())
         str << " [notify " << mp.notifySignal().name() << ']';
    return str;
}

QTextStream &operator<<(QTextStream &str, const QMetaMethod &m)
{
    switch (m.access()) {
    case QMetaMethod::Private:
        str << "private ";
        break;
    case QMetaMethod::Protected:
        str << "protected ";
        break;
    case QMetaMethod::Public:
        break;
    }
    str << m.typeName() << ' ' << m.methodSignature();
    switch (m.methodType()) {
    case QMetaMethod::Method:
        break;
    case QMetaMethod::Signal:
        str << " [signal]";
        break;
    case QMetaMethod::Slot:
        str << " [slot]";
        break;
    case QMetaMethod::Constructor:
        str << " [ct]";
        break;
    }
    if (auto attributes = m.attributes()) {
        str << " attributes: " << Qt::hex << Qt::showbase << attributes
            << Qt::dec << Qt::noshowbase;
    }
    if (const int count = m.parameterCount()) {
        str << " Parameters: ";
        const auto parameterNames = m.parameterNames();
        const auto parameterTypes = m.parameterTypes();
        for (int p = 0; p < count; ++p) {
            if (p)
                str << ", ";
            str << parameterTypes.at(p) << ' ' << parameterNames.at(p);
        }
    }
    return str;
}

static void formatMetaObject(QTextStream &str, const QMetaObject *mo, const  QByteArray &indent)
{
    str << indent << "--- " << mo->className() << " ---\n";

    const int classInfoOffset = mo->classInfoOffset();
    const int classInfoCount = mo->classInfoCount();
    if (classInfoOffset < classInfoCount) {
        str << indent << "  Class Info of " << mo->className() << ": "
            << classInfoOffset << ".." << classInfoCount << '\n';
        for (int i = classInfoOffset; i < classInfoCount; ++i) {
            str << indent << "    " << rightAlignNumber(i, 3) << ' '
                << mo->classInfo(i) << '\n';
        }
    }

    const int enumOffset = mo->enumeratorOffset();
    const int enumCount = mo->enumeratorCount();
    if (enumOffset < enumCount) {
        str << indent << "  Enums of " << mo->className() << ": " << enumOffset
            << ".." << enumCount << '\n';
        for (int e = enumOffset; e < enumCount; ++e)
            str << indent << "    " << rightAlignNumber(e, 3) << ' ' << mo->enumerator(e) << '\n';
    }

    const int methodOffset = mo->methodOffset();
    const int methodCount = mo->methodCount();
    if (methodOffset < methodCount) {
        str << indent << "  Methods of " << mo->className() << ": " << methodOffset
            << ".." << methodCount << '\n';
        for (int m = methodOffset; m < methodCount; ++m)
            str << indent << "    " << rightAlignNumber(m, 3) << ' ' << mo->method(m) << '\n';
    }

    const int propertyOffset = mo->propertyOffset();
    const int propertyCount = mo-> propertyCount();
    if (propertyOffset < propertyCount) {
        str << indent << "  Properties of " << mo->className() << ": " << propertyOffset
            << ".." << propertyCount << '\n';
        for (int p = propertyOffset; p < propertyCount; ++p)
            str << indent << "    " << rightAlignNumber(p, 3) << ' ' << mo->property(p) << '\n';
    }
}

QTextStream &operator<<(QTextStream &str, const QMetaObject &o)
{
    QVector<const QMetaObject *> klasses;
    for (auto s = &o; s; s = s->superClass())
        klasses.prepend(s);

    QByteArray indent;
    for (auto k : klasses) {
        formatMetaObject(str, k, indent);
        indent += "  ";
    }
    return str;
}

class TextDialog : public QDialog
{
public:
    explicit TextDialog(const QString &text, QWidget *parent = nullptr);
};

TextDialog::TextDialog(const QString &text, QWidget *parent) : QDialog(parent)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    auto layout = new QVBoxLayout(this);
    auto pe = new QPlainTextEdit(text, this);
    pe->setReadOnly(true);
    pe->setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));
    layout->addWidget(pe);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Close, this);
    layout->addWidget(buttonBox);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
    bool setControl(const QString &clsid);

public slots:
    void showMetaObject();

private:
    QAxWidget *m_axWidget;
};

MainWindow::MainWindow()
    : m_axWidget(new QAxWidget)
{
    const QString title = QGuiApplication::applicationDisplayName() + QLatin1String(" Qt ")
        + QLatin1String(QT_VERSION_STR) + QLatin1String(", ")
        + QString::number(QSysInfo::WordSize) + QLatin1String("bit");
    setWindowTitle(title);

    setObjectName(QLatin1String("MainWindow"));
    m_axWidget->setObjectName(QLatin1String("AxWidget"));

    setCentralWidget(m_axWidget);

    QMenu *fileMenu = menuBar()->addMenu(QLatin1String("File"));
    fileMenu->setObjectName(QLatin1String("FileMenu"));
    QToolBar *toolbar = new QToolBar;
    toolbar->setObjectName(QLatin1String("ToolBar"));
    addToolBar(Qt::TopToolBarArea, toolbar);

    QAction *action = fileMenu->addAction("Dump MetaObject",
                                          this, &MainWindow::showMetaObject);
    toolbar->addAction(action);
#ifdef QT_DIAG_LIB
    action = fileMenu->addAction("Dump Widgets",
                                 this, [] () { QtDiag::dumpAllWidgets(); });
    toolbar->addAction(action);
    action = fileMenu->addAction("Dump Windows",
                                 this, [] () { QtDiag::dumpAllWindows(); });
    toolbar->addAction(action);
    action = fileMenu->addAction("Dump Native Windows",
                                 this, [this] () { QtDiag::dumpNativeWindows(winId()); });
    toolbar->addAction(action);
    fileMenu->addSeparator();
#endif // QT_DIAG_LIB
    action = fileMenu->addAction("Quit", qApp, &QCoreApplication::quit);
    toolbar->addAction(action);
    action->setShortcut(Qt::CTRL + Qt::Key_Q);
}

bool MainWindow::setControl(const QString &clsid)
{
    const bool result = m_axWidget->setControl(clsid);
    if (result)
        statusBar()->showMessage(QLatin1String("Loaded ") + clsid);
    return result;
}

void MainWindow::showMetaObject()
{
    auto mo = m_axWidget->metaObject();
    QString dump;
    {
        QTextStream str(&dump);
        str << *mo;
    }
    auto dialog = new TextDialog(dump, this);
    dialog->setWindowTitle(QLatin1String("MetaObject of ") + QLatin1String(mo->className()));
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->resize(screen()->geometry().size() * 2 / 3);
    dialog->show();
}

int main(int argc, char* argv[])
{
    if (isOptionSet(argc, argv, "-s"))
        QCoreApplication::setAttribute(Qt::AA_DisableHighDpiScaling);
    if (!isOptionSet(argc, argv, "-n"))
        QCoreApplication::setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);

    QApplication app(argc, argv);
    QCoreApplication::setApplicationVersion(QLatin1String(QT_VERSION_STR));
    QGuiApplication::setApplicationName("Ax Viewer");

    QCommandLineParser parser;
    parser.setSingleDashWordOptionMode(QCommandLineParser::ParseAsLongOptions);
    parser.addHelpOption();
    parser.addVersionOption();
    QCommandLineOption noScalingDummy(QStringLiteral("s"),
                                      QStringLiteral("Set Qt::AA_DisableHighDpiScaling."));
    parser.addOption(noScalingDummy);
    QCommandLineOption nativeSiblingsDummy(QStringLiteral("n"),
                                           QStringLiteral("Do not set Qt::AA_DontCreateNativeWidgetSiblings."));
    parser.addOption(nativeSiblingsDummy);
    parser.addPositionalArgument(QStringLiteral("[clsid]"), QStringLiteral("Class ID"));

    parser.process(QCoreApplication::arguments());

    QString clsid = parser.positionalArguments().value(0, QString());
    if (clsid.isEmpty()) {
        QAxSelect select;
        if (select.exec() != QDialog::Accepted)
            return 0;
        clsid = select.clsid();
    }

    MainWindow mainWindow;

    qDebug() << QT_VERSION_STR << "Loading" << clsid;

    if (!mainWindow.setControl(clsid)) {
        qWarning().noquote().nospace() << "Failed to set \"" << clsid << '"';
        return -1;
    }

    mainWindow.show();
    return app.exec();
}

#include "main.moc"
