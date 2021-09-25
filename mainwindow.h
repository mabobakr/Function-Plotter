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

    bool generateXY(QVector<float> &x, QVector<float> &y, QString &text);
    float evalExpression(QString &text, float x);

    float applyOp(float a, float b, QChar op);

};
#endif // MAINWINDOW_H
