#include "mainwindow.h"
#include "./ui_mainwindow.h"

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


void MainWindow::on_pushButton_clicked()
{
    QString text = ui ->lineEdit->text();

    // Extract each term
    text.remove(' ');
    QRegularExpression reg("[\\+\\-\\*\\/\\^]");
    QStringList terms = text.split(reg, Qt::SkipEmptyParts);

    // to do: 1- check all terms are either X or numeric
    // 2-Save the sequence of operators and validate their order
    // 3- Generate Y & X
    // 4- plot

    for (int i = 0; i < terms.size(); i++)
        qDebug(terms[i].toUtf8());
}

