#include <QString>
#include <QtTest>

class TestDuplicatesFinder : public QObject
{
    Q_OBJECT
    
public:
    TestDuplicatesFinder();
    
private Q_SLOTS:
    void TestReduceList();
};

TestDuplicatesFinder::TestDuplicatesFinder()
{
}

void TestDuplicatesFinder::TestReduceList()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(TestDuplicatesFinder)

#include "tst_testduplicatesfinder.moc"
