#include <QString>
#include <QtTest>

#include "MeTeM_File_Manager/duplicatesfinder.h"

class TestMain : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    void TestSearch();
    void TestName();
    void TestSize();
    void TestSHA1();

private:
    FilesFinder* ff;
    DuplicatesFinder* df;

};

void TestMain::initTestCase()
{
    //Creating files for tests
    {
        if (!QDir("TestFiles").exists())
            QVERIFY(QDir().mkdir("TestFiles"));

        if (!QDir("TestFiles/other").exists())
            QVERIFY(QDir().mkdir("TestFiles/other"));

        QFile *testFiles[19];

        testFiles[0] = new QFile("TestFiles/1.test");
        testFiles[1] = new QFile("TestFiles/1copy1.test");
        testFiles[2] = new QFile("TestFiles/1copy2.test");
        testFiles[3] = new QFile("TestFiles/2.test");
        testFiles[4] = new QFile("TestFiles/3.test");
        testFiles[5] = new QFile("TestFiles/3copy1.test");
        testFiles[6] = new QFile("TestFiles/3copy2.test");
        testFiles[7] = new QFile("TestFiles/3copy3.test");
        testFiles[8] = new QFile("TestFiles/3copy4.test");
        testFiles[9] = new QFile("TestFiles/3copy5.test");
        testFiles[10] = new QFile("TestFiles/4.test");
        testFiles[11] = new QFile("TestFiles/5.test");
        testFiles[12] = new QFile("TestFiles/5bytes.test");
        testFiles[13] = new QFile("TestFiles/5bytesother.test");
        testFiles[14] = new QFile("TestFiles/5copy1.test");
        testFiles[15] = new QFile("TestFiles/other/1.test");
        testFiles[16] = new QFile("TestFiles/other/5.test");
        testFiles[17] = new QFile("TestFiles/xyz.test");
        testFiles[18] = new QFile("TestFiles/zyxv.test");

        for (int i = 0; i < 19; i++) QVERIFY(testFiles[i]->open(QIODevice::WriteOnly | QIODevice::Text));

        testFiles[0]->write("1");
        testFiles[1]->write("1");
        testFiles[2]->write("1");
        testFiles[3]->write("2");
        testFiles[4]->write("3");
        testFiles[5]->write("3");
        testFiles[6]->write("3");
        testFiles[7]->write("3");
        testFiles[8]->write("3");
        testFiles[9]->write("3");
        testFiles[10]->write("4");
        testFiles[11]->write("5");
        testFiles[12]->write("54321");
        testFiles[13]->write("12345");
        testFiles[14]->write("5");
        testFiles[15]->write("1");
        testFiles[16]->write("5");
        testFiles[17]->write("xyz");
        testFiles[18]->write("zyxv");

        for (int i = 0; i < 19; i++)
        {
            testFiles[i]->close();
            delete testFiles[i];
        }
    }

    ff = new FilesFinder("TestFiles");
    ff->SetNameFilters(QStringList("5*"));
    ff->IncludeSubdirs(true);

    df = new DuplicatesFinder("TestFiles");
    df->SetNameFilters(QStringList("*.test"));
    df->IncludeSubdirs(true);
}

void TestMain::cleanupTestCase()
{
    if (QDir("TestFiles").exists())
        QVERIFY(QDir("TestFiles").removeRecursively());

    delete ff;
    delete df;
}

void TestMain::TestSearch()
{
    ff->Search();
    QList<FileInfoEx> list = ff->GetResult();

    QVERIFY(list.contains(FileInfoEx("TestFiles/5.test")));
    QVERIFY(list.contains(FileInfoEx("TestFiles/5bytes.test")));
    QVERIFY(list.contains(FileInfoEx("TestFiles/5bytesother.test")));
    QVERIFY(list.contains(FileInfoEx("TestFiles/5copy1.test")));
    QVERIFY(list.contains(FileInfoEx("TestFiles/other/5.test")));
    QVERIFY2((list.count() == 5), "Wrong list size (search by 5* pattern)");
}

void TestMain::TestName()
{
    df->SetMethods(DuplicatesFinder::Name);
    df->Search();
    QList<FileInfoEx> list = df->GetResult();

    QVERIFY(list.contains(FileInfoEx("TestFiles/1.test")));
    QVERIFY(list.contains(FileInfoEx("TestFiles/5.test")));
    QVERIFY(list.contains(FileInfoEx("TestFiles/other/1.test")));
    QVERIFY(list.contains(FileInfoEx("TestFiles/other/5.test")));
    QVERIFY2((list.count() == 4), "Wrong list size (search by name)");
}

void TestMain::TestSize()
{
    df->SetMethods(DuplicatesFinder::Size);
    df->Search();
    QList<FileInfoEx> list = df->GetResult();

    QVERIFY(list.contains(FileInfoEx("TestFiles/1.test")));
    QVERIFY(list.contains(FileInfoEx("TestFiles/1copy1.test")));
    QVERIFY(list.contains(FileInfoEx("TestFiles/1copy2.test")));
    QVERIFY(list.contains(FileInfoEx("TestFiles/2.test")));
    QVERIFY(list.contains(FileInfoEx("TestFiles/3.test")));
    QVERIFY(list.contains(FileInfoEx("TestFiles/3copy1.test")));
    QVERIFY(list.contains(FileInfoEx("TestFiles/3copy2.test")));
    QVERIFY(list.contains(FileInfoEx("TestFiles/3copy3.test")));
    QVERIFY(list.contains(FileInfoEx("TestFiles/3copy4.test")));
    QVERIFY(list.contains(FileInfoEx("TestFiles/3copy5.test")));
    QVERIFY(list.contains(FileInfoEx("TestFiles/4.test")));
    QVERIFY(list.contains(FileInfoEx("TestFiles/5.test")));
    QVERIFY(list.contains(FileInfoEx("TestFiles/5bytes.test")));
    QVERIFY(list.contains(FileInfoEx("TestFiles/5bytesother.test")));
    QVERIFY(list.contains(FileInfoEx("TestFiles/5copy1.test")));
    QVERIFY(list.contains(FileInfoEx("TestFiles/other/1.test")));
    QVERIFY(list.contains(FileInfoEx("TestFiles/other/5.test")));
    QVERIFY2((list.count() == 17), "Wrong list size (search by size)");
}

void TestMain::TestSHA1()
{
    df->SetMethods(DuplicatesFinder::SizeAndSha1);
    df->Search();
    QList<FileInfoEx> list = df->GetResult();

    QVERIFY(list.contains(FileInfoEx("TestFiles/1.test")));
    QVERIFY(list.contains(FileInfoEx("TestFiles/1copy1.test")));
    QVERIFY(list.contains(FileInfoEx("TestFiles/1copy2.test")));
    QVERIFY(list.contains(FileInfoEx("TestFiles/3.test")));
    QVERIFY(list.contains(FileInfoEx("TestFiles/3copy1.test")));
    QVERIFY(list.contains(FileInfoEx("TestFiles/3copy2.test")));
    QVERIFY(list.contains(FileInfoEx("TestFiles/3copy3.test")));
    QVERIFY(list.contains(FileInfoEx("TestFiles/3copy4.test")));
    QVERIFY(list.contains(FileInfoEx("TestFiles/3copy5.test")));
    QVERIFY(list.contains(FileInfoEx("TestFiles/5.test")));
    QVERIFY(list.contains(FileInfoEx("TestFiles/5copy1.test")));
    QVERIFY(list.contains(FileInfoEx("TestFiles/other/1.test")));
    QVERIFY(list.contains(FileInfoEx("TestFiles/other/5.test")));
    QVERIFY2((list.count() == 13), "Wrong list size (search by sha1)");

    QCOMPARE(list[list.indexOf(FileInfoEx("TestFiles/1.test"))].GetSHA1().toHex().data(), "356a192b7913b04c54574d18c28d46e6395428ab");
    QCOMPARE(list[list.indexOf(FileInfoEx("TestFiles/1copy1.test"))].GetSHA1().toHex().data(), "356a192b7913b04c54574d18c28d46e6395428ab");
    QCOMPARE(list[list.indexOf(FileInfoEx("TestFiles/1copy2.test"))].GetSHA1().toHex().data(), "356a192b7913b04c54574d18c28d46e6395428ab");
    QCOMPARE(list[list.indexOf(FileInfoEx("TestFiles/3.test"))].GetSHA1().toHex().data(), "77de68daecd823babbb58edb1c8e14d7106e83bb");
    QCOMPARE(list[list.indexOf(FileInfoEx("TestFiles/3copy1.test"))].GetSHA1().toHex().data(), "77de68daecd823babbb58edb1c8e14d7106e83bb");
    QCOMPARE(list[list.indexOf(FileInfoEx("TestFiles/3copy2.test"))].GetSHA1().toHex().data(), "77de68daecd823babbb58edb1c8e14d7106e83bb");
    QCOMPARE(list[list.indexOf(FileInfoEx("TestFiles/3copy3.test"))].GetSHA1().toHex().data(), "77de68daecd823babbb58edb1c8e14d7106e83bb");
    QCOMPARE(list[list.indexOf(FileInfoEx("TestFiles/3copy4.test"))].GetSHA1().toHex().data(), "77de68daecd823babbb58edb1c8e14d7106e83bb");
    QCOMPARE(list[list.indexOf(FileInfoEx("TestFiles/3copy5.test"))].GetSHA1().toHex().data(), "77de68daecd823babbb58edb1c8e14d7106e83bb");
    QCOMPARE(list[list.indexOf(FileInfoEx("TestFiles/5.test"))].GetSHA1().toHex().data(), "ac3478d69a3c81fa62e60f5c3696165a4e5e6ac4");
    QCOMPARE(list[list.indexOf(FileInfoEx("TestFiles/5copy1.test"))].GetSHA1().toHex().data(), "ac3478d69a3c81fa62e60f5c3696165a4e5e6ac4");
    QCOMPARE(list[list.indexOf(FileInfoEx("TestFiles/other/1.test"))].GetSHA1().toHex().data(), "356a192b7913b04c54574d18c28d46e6395428ab");
    QCOMPARE(list[list.indexOf(FileInfoEx("TestFiles/other/5.test"))].GetSHA1().toHex().data(), "ac3478d69a3c81fa62e60f5c3696165a4e5e6ac4");
}

QTEST_APPLESS_MAIN(TestMain)

#include "tst_main.moc"
