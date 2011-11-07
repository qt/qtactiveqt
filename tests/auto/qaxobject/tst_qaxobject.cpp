#include <QtTest/QtTest>
#include <QAxObject>

class tst_QAxObject : public QObject
{
    Q_OBJECT

private slots:
    void propertyByRefWritable();
    void setPropertyByRef();
};

void tst_QAxObject::propertyByRefWritable()
{
    const QAxObject speak("SAPI.SPVoice");
    const QMetaObject *metaObject = speak.metaObject();

    for (int i = 0; i < metaObject->propertyCount(); ++i) {
        if (metaObject->property(i).name() == QLatin1String("Voice")) {
            QVERIFY(metaObject->property(i).isWritable());
            break;
        }
    }
}

void tst_QAxObject::setPropertyByRef()
{
    QAxObject speak("SAPI.SPVoice");

    QVERIFY(speak.setProperty("Voice", speak.property("Voice")));
}

QTEST_MAIN(tst_QAxObject)
#include "tst_qaxobject.moc"
