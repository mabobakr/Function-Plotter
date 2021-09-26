#include <QtTest>
#include <QCoreApplication>

#include "calculator.h"

// add necessary includes here

class CalculatorTesting : public QObject
{
    Q_OBJECT

public:
    CalculatorTesting();
    ~CalculatorTesting();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_constructor();
    void test_isOp();
    void test_applyOp();
    void test_preced();

};

CalculatorTesting::CalculatorTesting()
{

}

CalculatorTesting::~CalculatorTesting()
{

}

void CalculatorTesting::initTestCase()
{

}

void CalculatorTesting::cleanupTestCase()
{

}

void CalculatorTesting::test_constructor()
{
    // Empty text
    QVERIFY_EXCEPTION_THROWN(Calculator c("", 0, 0, 0), char *);

    // invalid range
    QVERIFY_EXCEPTION_THROWN(Calculator c("x + 3", 0, -1, 0), char *);

    // if data is valid x and y are resized to dataSize
    int dataSize = 100;
    Calculator c("x + 3", -1, 1, dataSize);
    QCOMPARE(c.x.size(), dataSize);
    QCOMPARE(c.x.size(), dataSize);
}

void CalculatorTesting::test_isOp(){
    // Operators should return true
    QVERIFY(isOp('+'));
    QVERIFY(isOp('-'));
    QVERIFY(isOp('*'));
    QVERIFY(isOp('/'));
    QVERIFY(isOp('^'));

    // if not operator return false
    QEXPECT_FAIL("", "not an operator", Continue);
    QVERIFY(isOp('x'));

    QEXPECT_FAIL("", "not an operator", Continue);
    QVERIFY(isOp('1'));

}

void CalculatorTesting::test_applyOp(){
    double x = 8, y = 2;
    QCOMPARE(applyOp(x, y, '+'), 10);
    QCOMPARE(applyOp(x, y, '-'), 6);
    QCOMPARE(applyOp(x, y, '*'), 16);
    QCOMPARE(applyOp(x, y, '/'), 4);
    QCOMPARE(applyOp(x, y, '^'), 64);
}

void CalculatorTesting::test_preced(){
    QCOMPARE(preced('+'), 1);
    QCOMPARE(preced('-'), 1);
    QCOMPARE(preced('*'), 2);
    QCOMPARE(preced('/'), 2);
    QCOMPARE(preced('^'), 3);
}

QTEST_MAIN(CalculatorTesting)

#include "tst_calculatortesting.moc"
