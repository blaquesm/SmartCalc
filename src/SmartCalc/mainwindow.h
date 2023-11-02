#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <graphic.h>

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
    void operators();
    void functions();
    void drop();
    void skob();
    void unar();
    void clean();
    void x();
    void eq();
    void graphic();

private:
    Ui::MainWindow *ui;
    bool IsOperator(QChar symbol);
    int FirstDigit(QString string_digit, int id_x);
    Graphic graph_q;
};
#endif // MAINWINDOW_H
