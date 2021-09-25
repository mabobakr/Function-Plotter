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

// Plots the graph
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
        // Get input from gui
        QString text = ui ->lineEdit->text();
        double xMin = ui ->xMin->value(), xMax = ui ->xMax->value();

        // size of data in the range
        int size = 100;

        // Create a Calculator object & calculate f(x)
        Calculator calcObj(text, xMin, xMax, size);
        calcObj.calculateY();

        // plot the function
        plot(calcObj.x, calcObj.y);
    }
    catch (const char *msg) {
        // Display message in a message box
        QMessageBox msgBox;
        msgBox.setText(msg);
        msgBox.exec();
    }
}

