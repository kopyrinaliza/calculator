#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

namespace Ui {
class calculator;
}

class calculator : public QMainWindow
{
    Q_OBJECT

public:
    explicit calculator(QWidget *parent = nullptr);
    ~calculator();

    int count = 0;
private:
    Ui::calculator *ui;
private slots:
    void digits_numbers();
    void on_pushButton_dot_clicked();
    void operations();
    void on_pushButton_clear_clicked();
    void on_pushButton_equal_clicked();
    void math_operations();
    void on_btn_clear_clicked();
    void on_btnMove_clicked();
};

#endif // CALCULATOR_H
