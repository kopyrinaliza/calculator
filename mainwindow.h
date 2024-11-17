#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <calculator.h>
#include <matrix.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushChisla_clicked();
    void on_buttonMatrix_clicked();
private:
    Ui::MainWindow *ui;
    calculator calculator;
    matrix matrix;
};

#endif // MAINWINDOW_H
