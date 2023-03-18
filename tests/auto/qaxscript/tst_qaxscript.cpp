// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0


#include <QtTest/QtTest>
#include <QAxScriptManager>
#include <QAxScript>

using namespace Qt::StringLiterals;

class tst_QAxScript : public QObject
{
    Q_OBJECT

private slots:
    void scriptReturnValue();
};

void tst_QAxScript::scriptReturnValue()
{
    QAxScriptManager scriptManager;
    const auto scriptCode = uR"JS(
    function foo() {
        return 'test';
    }
    )JS"_s;  // QTBUG-42289, fails when DISPATCH_PROPERTYGET is used.
    QAxScript *script = scriptManager.load(scriptCode, u"Test"_s, u"JScript"_s);
    QVERIFY2(script, "Unable to load script (CoInitializeEx() called?)");
    const QVariant result = script->call("foo()");
    QCOMPARE(result, QVariant(u"test"_s));
}

QTEST_MAIN(tst_QAxScript)
#include "tst_qaxscript.moc"
