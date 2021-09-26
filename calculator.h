#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QVector>
#include <QStack>
#include <math.h>

// Utility functions declaration
bool isOp(QChar x);
int preced(QChar x);
double applyOp(double a, double b, QChar op);


class Calculator
{

private:
    double xMin, xMax;
    QString text;

    int dataSize;

public:
    QVector<double> x, y;

    Calculator();
    Calculator(QString text, double xMin, double xMax, int dataSize);
    double evalExpression(double x);
    void calculateY();
};

#endif // CALCULATOR_H
