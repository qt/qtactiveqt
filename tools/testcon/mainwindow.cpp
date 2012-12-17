/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the tools applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "mainwindow.h"
#include "changeproperties.h"
#include "invokemethod.h"
#include "ambientproperties.h"
#include "controlinfo.h"
#include "docuwindow.h"

#include <QtWidgets/QMdiArea>
#include <QtWidgets/QMdiSubWindow>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QInputDialog>
#include <QtWidgets/QMessageBox>
#include <QtCore/qt_windows.h>
#include <ActiveQt/QAxScriptManager>
#include <ActiveQt/QAxSelect>
#include <ActiveQt/QAxWidget>
#include <ActiveQt/qaxtypes.h>

QT_BEGIN_NAMESPACE

QAxObject *ax_mainWindow = 0;

static QTextEdit *debuglog = 0;

static void redirectDebugOutput(QtMsgType type, const QMessageLogContext &, const QString &msg)
{
    Q_UNUSED(type);
    debuglog->append(msg);
}

QT_END_NAMESPACE

QT_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);
    setObjectName(QLatin1String("MainWindow"));

    QAxScriptManager::registerEngine(QLatin1String("PerlScript"), QLatin1String(".pl"));
    QAxScriptManager::registerEngine(QLatin1String("Python"), QLatin1String(".py"));

    dlgInvoke = 0;
    dlgProperties = 0;
    dlgAmbient = 0;
    scripts = 0;
    debuglog = logDebug;
    oldDebugHandler = qInstallMessageHandler(redirectDebugOutput);
    QHBoxLayout *layout = new QHBoxLayout(Workbase);
    mdiArea = new QMdiArea(Workbase);
    layout->addWidget(mdiArea);
    layout->setMargin(0);

    connect(mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(updateGUI()));
    connect(actionFileExit, SIGNAL(triggered()), qApp, SLOT(quit()));
}

MainWindow::~MainWindow()
{
    qInstallMessageHandler(oldDebugHandler);
    debuglog = 0;
}

QAxWidget *MainWindow::activeAxWidget() const
{
    if (const QMdiSubWindow *activeSubWindow = mdiArea->currentSubWindow())
        return qobject_cast<QAxWidget*>(activeSubWindow->widget());
    return 0;
}

QList<QAxWidget *> MainWindow::axWidgets() const
{
    QList<QAxWidget *> result;
    foreach (const QMdiSubWindow *subWindow, mdiArea->subWindowList())
        if (QAxWidget *axWidget = qobject_cast<QAxWidget *>(subWindow->widget()))
            result.push_back(axWidget);
    return result;
}

void MainWindow::on_actionFileNew_triggered()
{
    QAxSelect select(this);
    if (select.exec()) {
        QAxWidget *container = new QAxWidget;
        container->setControl(select.clsid());
        container->setObjectName(container->windowTitle());
        mdiArea->addSubWindow(container);
        container->show();
    }
    updateGUI();
}

void MainWindow::on_actionFileLoad_triggered()
{
    QString fname = QFileDialog::getOpenFileName(this, tr("Load"), QString(), QLatin1String("*.qax"));
    if (fname.isEmpty())
	return;

    QFile file(fname);
    if (!file.open(QIODevice::ReadOnly)) {
	QMessageBox::information(this, tr("Error Loading File"), tr("The file could not be opened for reading.\n%1").arg(fname));
	return;
    }

    QAxWidget *container = new QAxWidget(mdiArea);
    container->setObjectName(container->windowTitle());

    QDataStream d(&file);
    d >> *container;

    mdiArea->addSubWindow(container);
    container->show();

    updateGUI();
}

void MainWindow::on_actionFileSave_triggered()
{
    QAxWidget *container = activeAxWidget();
    if (!container)
        return;

    QString fname = QFileDialog::getSaveFileName(this, tr("Save"), QString(), QLatin1String("*.qax"));
    if (fname.isEmpty())
	return;

    QFile file(fname);
    if (!file.open(QIODevice::WriteOnly)) {
	QMessageBox::information(this, tr("Error Saving File"), tr("The file could not be opened for writing.\n%1").arg(fname));
	return;
    }
    QDataStream d(&file);
    d << *container;
}


void MainWindow::on_actionContainerSet_triggered()
{
    QAxWidget *container = activeAxWidget();
    if (!container)
        return;

    QAxSelect select(this);
    if (select.exec())
	container->setControl(select.clsid());
    updateGUI();
}

void MainWindow::on_actionContainerClear_triggered()
{
    QAxWidget *container = activeAxWidget();
    if (container)
	container->clear();
    updateGUI();
}

void MainWindow::on_actionContainerProperties_triggered()
{
    if (!dlgAmbient) {
	dlgAmbient = new AmbientProperties(this);
        dlgAmbient->setControl(mdiArea);
    }
    dlgAmbient->show();
}


void MainWindow::on_actionControlInfo_triggered()
{
    QAxWidget *container = activeAxWidget();
    if (!container)
        return;

    ControlInfo info(this);
    info.setControl(container);
    info.exec();
}

void MainWindow::on_actionControlProperties_triggered()
{
    QAxWidget *container = activeAxWidget();
    if (!container)
        return;

    if (!dlgProperties) {
	dlgProperties = new ChangeProperties(this);
	connect(container, SIGNAL(propertyChanged(QString)), dlgProperties, SLOT(updateProperties()));
    }
    dlgProperties->setControl(container);
    dlgProperties->show();
}

void MainWindow::on_actionControlMethods_triggered()
{
    QAxWidget *container = activeAxWidget();
    if (!container)
        return;

    if (!dlgInvoke)
	dlgInvoke = new InvokeMethod(this);
    dlgInvoke->setControl(container);
    dlgInvoke->show();
}

void MainWindow::on_VerbMenu_aboutToShow()
{
    VerbMenu->clear();

    QAxWidget *container = activeAxWidget();
    if (!container)
        return;

    QStringList verbs = container->verbs();
    for (int i = 0; i < verbs.count(); ++i) {
        VerbMenu->addAction(verbs.at(i));
    }

    if (!verbs.count()) { // no verbs?
        VerbMenu->addAction(tr("-- Object does not support any verbs --"))->setEnabled(false);
    }
}

void MainWindow::on_VerbMenu_triggered(QAction *action)
{
    QAxWidget *container = activeAxWidget();
    if (!container)
        return;

    container->doVerb(action->text());
}

void MainWindow::on_actionControlDocumentation_triggered()
{
    QAxWidget *container = activeAxWidget();
    if (!container)
        return;
    
    const QString docu = container->generateDocumentation();
    if (docu.isEmpty())
	return;

    DocuWindow *docwindow = new DocuWindow(docu);
    QMdiSubWindow *subWindow = mdiArea->addSubWindow(docwindow);
    subWindow->setWindowTitle(DocuWindow::tr("%1 - Documentation").arg(container->windowTitle()));
    docwindow->show();
}

void MainWindow::on_actionControlPixmap_triggered()
{
    QAxWidget *container = activeAxWidget();
    if (!container)
        return;

    QLabel *label = new QLabel;
    label->setPixmap(QPixmap::grabWidget(container));
    QMdiSubWindow *subWindow = mdiArea->addSubWindow(label);
    subWindow->setWindowTitle(tr("%1 - Pixmap").arg(container->windowTitle()));
    label->show();
}

void MainWindow::on_actionScriptingRun_triggered()
{
#ifndef QT_NO_QAXSCRIPT
    if (!scripts)
	return;

    // If we have only one script loaded we can use the cool dialog
    QStringList scriptList = scripts->scriptNames();
    if (scriptList.count() == 1) {
	InvokeMethod scriptInvoke(this);
	scriptInvoke.setWindowTitle(tr("Execute Script Function"));
	scriptInvoke.setControl(scripts->script(scriptList[0])->scriptEngine());
	scriptInvoke.exec();
	return;
    }

    bool ok = false;
    QStringList macroList = scripts->functions(QAxScript::FunctionNames);
    QString macro = QInputDialog::getItem(this, tr("Select Macro"), tr("Macro:"), macroList, 0, true, &ok);

    if (!ok)
	return;

    QVariant result = scripts->call(macro);
    if (result.isValid())
	logMacros->append(tr("Return value of %1: %2").arg(macro).arg(result.toString()));
#endif
}

void MainWindow::on_actionScriptingLoad_triggered()
{
#ifndef QT_NO_QAXSCRIPT
    QString file = QFileDialog::getOpenFileName(this, tr("Open Script"), QString(), QAxScriptManager::scriptFileFilter());

    if (file.isEmpty())
	return;

    if (!scripts) {
	scripts = new QAxScriptManager(this);
	scripts->addObject(this);
    }

    foreach (QAxWidget *axWidget, axWidgets()) {
        QAxBase *ax = axWidget;
        scripts->addObject(ax);
    }

    QAxScript *script = scripts->load(file, file);
    if (script) {
	connect(script, SIGNAL(error(int,QString,int,QString)),
		this,   SLOT(logMacro(int,QString,int,QString)));
	actionScriptingRun->setEnabled(true);
    }
#else
    QMessageBox::information(this, tr("Function not available"),
	tr("QAxScript functionality is not available with this compiler."));
#endif
}

void MainWindow::updateGUI()
{
    QAxWidget *container = activeAxWidget();

    bool hasControl = container && !container->isNull();
    actionFileNew->setEnabled(true);
    actionFileLoad->setEnabled(true);
    actionFileSave->setEnabled(hasControl);
    actionContainerSet->setEnabled(container != 0);
    actionContainerClear->setEnabled(hasControl);
    actionControlProperties->setEnabled(hasControl);
    actionControlMethods->setEnabled(hasControl);
    actionControlInfo->setEnabled(hasControl);
    actionControlDocumentation->setEnabled(hasControl);
    actionControlPixmap->setEnabled(hasControl);
    VerbMenu->setEnabled(hasControl);
    if (dlgInvoke)
	dlgInvoke->setControl(hasControl ? container : 0);
    if (dlgProperties)
	dlgProperties->setControl(hasControl ? container : 0);

    foreach (QAxWidget *container, axWidgets()) {
        container->disconnect(SIGNAL(signal(QString,int,void*)));
	    if (actionLogSignals->isChecked())
		connect(container, SIGNAL(signal(QString,int,void*)), this, SLOT(logSignal(QString,int,void*)));

	    container->disconnect(SIGNAL(exception(int,QString,QString,QString)));
	    connect(container, SIGNAL(exception(int,QString,QString,QString)),
		this, SLOT(logException(int,QString,QString,QString)));

	    container->disconnect(SIGNAL(propertyChanged(QString)));
	    if (actionLogProperties->isChecked()) 
		connect(container, SIGNAL(propertyChanged(QString)), this, SLOT(logPropertyChanged(QString)));
	    container->blockSignals(actionFreezeEvents->isChecked());
	}
}

void MainWindow::logPropertyChanged(const QString &prop)
{
    QAxWidget *container = activeAxWidget();
    if (!container)
        return;

    QVariant var = container->property(prop.toLatin1());
    logProperties->append(tr("%1: Property Change: %2 - { %3 }").arg(container->windowTitle(), prop, var.toString()));
}

void MainWindow::logSignal(const QString &signal, int argc, void *argv)
{
    QAxWidget *container = activeAxWidget();
    if (!container)
        return;

    QString paramlist;
    VARIANT *params = (VARIANT*)argv;
    for (int a = argc-1; a >= 0; --a) {
	if (a == argc-1)
	    paramlist = QLatin1String(" - {");
	QVariant qvar = VARIANTToQVariant(params[a], 0);
	paramlist += QLatin1String(" ") + qvar.toString();
	if (a > 0)
	    paramlist += QLatin1String(",");
	else
	    paramlist += QLatin1String(" ");
    }
    if (argc)
	paramlist += QLatin1String("}");
    logSignals->append(container->windowTitle() + QLatin1String(": ") + signal + paramlist);
}

void MainWindow::logException(int code, const QString&source, const QString&desc, const QString&help)
{
    Q_UNUSED(desc);
    QAxWidget *container = qobject_cast<QAxWidget*>(sender());
    if (!container)
        return;

    QString str = tr("%1: Exception code %2 thrown by %3").
	arg(container->windowTitle()).arg(code).arg(source);
    logDebug->append(str);
    logDebug->append(tr("\tDescription: %1").arg(desc));

    if (!help.isEmpty())
	logDebug->append(tr("\tHelp available at %1").arg(help));
    else
	logDebug->append(tr("\tNo help available."));
}

void MainWindow::logMacro(int code, const QString &description, int sourcePosition, const QString &sourceText)
{
    /* FIXME This needs to be rewritten to not use string concatentation, such
     * that it can be translated in a sane way. */
    QString message = tr("Script: ");
    if (code)
	message += QString::number(code) + QLatin1String(" ");
    message += QLatin1String("'") + description + QLatin1String("'");
    if (sourcePosition)
	message += tr(" at position ") + QString::number(sourcePosition);
    if (!sourceText.isEmpty())
	message += QLatin1String(" '") + sourceText + QLatin1String("'");

    logMacros->append(message);
}
