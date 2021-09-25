#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStack>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    bool generateXY(QVector<double> &x, QVector<double> &y, QString &text);
    double evalExpression(QString &text, double x);
    void plot(QVector<double> &x, QVector<double> &y);

    double applyOp(double a, double b, QChar op);

};
#endif // MAINWINDOW_H
