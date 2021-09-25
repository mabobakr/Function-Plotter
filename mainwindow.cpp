#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::generateXY(QVector<double> &x, QVector<double> &y, QString &text){

    double xMin = ui ->xMin->value(), xMax = ui ->xMax->value();

    // Check if range is valid
    if (xMin >= xMax) throw "Max must be higher than Min";

    int n = x.size();
    for (int i = 0; i < x.size(); i++){
        // Create range of x from xMin to xMax (linear equation in i)
        x[i] = xMin + i * (xMax-xMin) / (n-1);

        // Evaluate expression to get corresponding y
        y[i] = evalExpression(text, x[i]);
        //qDebug() << x[i] << y[i];
    }
}

// evaluate the expression to get y of the given x
double MainWindow::evalExpression(QString &text, double x){
    QChar op;
    double a, b;
    int n = text.size();
    int temp = 0;
    QStack<double> values;
    QStack<QChar> operators;

    if (isOp(text[0]) || isOp(text[n - 1])){
            throw "Function cannot start or end with an operator";
    }

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
            throw "Only valid symbols are + , - , * , ^ , / and numeric digits";
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

void MainWindow::plot(QVector<double> &x, QVector<double> &y) {
   // add graph & set data
   ui ->plotWidget->addGraph();
   ui ->plotWidget->graph(0)->setData(x, y);

   // set labels
   ui ->plotWidget->xAxis->setLabel("X");
   ui ->plotWidget->yAxis->setLabel("Y");

   int n = x.size();
   // set range for each axis
   ui->plotWidget->xAxis->setRange(x[0], x[n-1]);
   ui->plotWidget->yAxis->setRange(y[0], y[n-1]);

   // plot
   ui ->plotWidget ->replot();
}

void MainWindow::on_pushButton_clicked()
{
    try {
        QString text = ui ->lineEdit->text();
        if (text == "") throw "Please enter a function";

        // remove whitespace & convert X to lowercase
        text.remove(' ');
        text = text.toLower();

        // size of data in the range
        int size = 100;
        QVector<double> x(size), y(size);

        // Generate plotting data X and Y
        generateXY(x, y, text);

        // Plot the function
        plot(x, y);
    }
    catch (const char *msg) {
        // Display message in a message box
        QMessageBox msgBox;
        msgBox.setText(msg);
        msgBox.exec();
    }


}

