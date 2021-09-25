#include "calculator.h"
#include <stdio.h>
#include <iostream>

using namespace std;
Calculator::Calculator()
{}

Calculator::Calculator(QString text, double xMin, double xMax, int dataSize): xMin(xMin), xMax(xMax),
text(text), dataSize(dataSize){
    // remove whitespace & convert X to lowercase
    this->text.remove(' ');
    this->text = this->text.toLower();

    if (text == "") throw "Please enter a function";

    // Check if range is valid
    if (xMin >= xMax) throw "Max must be higher than Min";
    x.resize(dataSize);
    y.resize(dataSize);
}



// Applies one of the allowed operations on 2 operands
double applyOp(double a, double b, QChar op){
    switch(op.unicode()) {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    case '^':
        return pow(a, b);
    default:
        return -1;
    }
}


bool isOp(QChar x){
    return (x == '+' || x == '-' || x == '*' || x == '/' || x == '^');
}

// Determine the precedence of an operator
int preced(QChar x) {
    return (x == '^')? 3 :
           (x == '*' || x == '/')? 2 : 1;
}

void Calculator::calculateY(){
    for (int i = 0; i < dataSize; i++){
        // Create range of x from xMin to xMax (linear equation in i)
        x[i] = xMin + i * (xMax-xMin) / (dataSize-1);

        // Evaluate expression to get corresponding y
        y[i] = evalExpression(x[i]);
    }
}

// evaluate the expression to get y of the given x
double Calculator::evalExpression(double x){
    QChar op;
    double a, b;
    int n = text.size(), temp = 0;
    QStack<double> values;
    QStack<QChar> operators;

    if (isOp(text[0]) || isOp(text[n - 1])){
            throw "Function cannot start or end with an operator";
    }

    // last character was operator
    bool lastOp = false;

    for (int i = 0; i < n; i++){
        if (text[i].isDigit()) {
            // push whole number to values stack
            temp = text[i].digitValue();
            while(i+1 < n && text[i+1].isDigit()){
                i++;
                temp = 10 * temp + text[i].digitValue();
            }

            values.push(temp);
            lastOp = false;
        }
        else if (text[i] == 'x') {
            lastOp = false;
            values.push(x);
        }
        else if (isOp(text[i])){
            if (lastOp) throw "Function can't have two successive operators";
            lastOp = true;
            // Solve prior operators with higher or equal precedence
            while (!operators.isEmpty() && preced(operators.top()) >= preced(text[i])){
                op = operators.pop();
                b = values.pop();
                a = values.pop();
                values.push(applyOp(a, b, op));
            }

            // push current operator
            operators.push(text[i]);
        }
        else {
            throw "Supported symbols are + , - , * , ^ , / and numeric digits";
        }
    }

    // Solve remaining operators
    while (!operators.isEmpty()) {
        op = operators.pop();
        b = values.pop();
        a = values.pop();
        values.push(applyOp(a, b, op));
    }

    if (values.size() > 1) throw "Expression can't have successive values without operators";
    return values.pop();
}



