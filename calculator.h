#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QVector>
#include <QStack>
#include <math.h>

class Calculator
{

private:
    double xMin, xMax;
    QString text;

    int dataSize;

    double evalExpression(double x);

public:
    QVector<double> x, y;

    Calculator();
    Calculator(QString text, double xMin, double xMax, int dataSize);
    void calculateY();
};

#endif // CALCULATOR_H