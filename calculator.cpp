#include "calculator.h"
#include "ui_calculator.h"
#include <QtWidgets>

double num_first;

calculator::calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::calculator)
{
    ui->setupUi(this);

    connect(ui->pushButton_0, SIGNAL(clicked()),this, SLOT(digits_numbers()));
    connect(ui->pushButton_1, SIGNAL(clicked()),this, SLOT(digits_numbers()));
    connect(ui->pushButton_2, SIGNAL(clicked()),this, SLOT(digits_numbers()));
    connect(ui->pushButton_3, SIGNAL(clicked()),this, SLOT(digits_numbers()));
    connect(ui->pushButton_4, SIGNAL(clicked()),this, SLOT(digits_numbers()));
    connect(ui->pushButton_5, SIGNAL(clicked()),this, SLOT(digits_numbers()));
    connect(ui->pushButton_6, SIGNAL(clicked()),this, SLOT(digits_numbers()));
    connect(ui->pushButton_7, SIGNAL(clicked()),this, SLOT(digits_numbers()));
    connect(ui->pushButton_8, SIGNAL(clicked()),this, SLOT(digits_numbers()));
    connect(ui->pushButton_9, SIGNAL(clicked()),this, SLOT(digits_numbers()));
    connect(ui->pushButton_plusminus, SIGNAL(clicked()),this, SLOT(operations()));
    connect(ui->pushButton_percent, SIGNAL(clicked()),this, SLOT(operations()));
    connect(ui->pushButton_div, SIGNAL(clicked()),this, SLOT(math_operations()));
    connect(ui->pushButton_minus, SIGNAL(clicked()),this, SLOT(math_operations()));
    connect(ui->pushButton_plus, SIGNAL(clicked()),this, SLOT(math_operations()));
    connect(ui->pushButton_multi, SIGNAL(clicked()),this, SLOT(math_operations()));

    ui->pushButton_div->setCheckable(true);
    ui->pushButton_minus->setCheckable(true);
    ui->pushButton_plus->setCheckable(true);
    ui->pushButton_multi->setCheckable(true);
}

calculator::~calculator()
{
    delete ui;
}

void calculator::digits_numbers()
{
    QPushButton *button = (QPushButton *)sender();

    double all_numbers;
    QString new_label;
    if (ui->label->text().contains(".") && button->text() == "0"){
        new_label = ui->label->text() + button->text();
    } else {
        all_numbers = (ui->label->text()+button->text()).toDouble();
        new_label = QString::number(all_numbers);
    }
    ui->label->setText(new_label);

}

void calculator::on_pushButton_dot_clicked()
{
    if(!(ui->label->text().contains('.'))){
        ui->label->setText(ui->label->text() + ".");
    }
}

void calculator::operations()
{
    QPushButton *button = (QPushButton *)sender();

    double all_numbers;
    QString new_label;

    if(button->text() == "+/-"){
        all_numbers = (ui->label->text()).toDouble();
        all_numbers = all_numbers * -1;
        new_label = QString::number(all_numbers);
        ui->label->setText(new_label);
    } else if(button->text() == "%"){
        all_numbers = (ui->label->text()).toDouble();
        all_numbers = all_numbers * 0.01;
        new_label = QString::number(all_numbers);
        ui->label->setText(new_label);

        QVBoxLayout* layout = ui->layout;
        QLabel* newLabel = new QLabel(new_label);
        count = count + 1;
        newLabel->setObjectName(QString("label%1").arg(count));
        QCheckBox* check = new QCheckBox(tr("Процент"));
        check->setObjectName(QString("check%1").arg(count));
        layout->addWidget(newLabel);
        layout->addWidget(check);
    }
}

void calculator::math_operations()
{
    QPushButton *button = (QPushButton *)sender();

    num_first = ui->label->text().toDouble();
    ui->label->setText("");
    button->setChecked(true);
}
void calculator::on_pushButton_clear_clicked()
{
    ui->pushButton_plus->setChecked(false);
    ui->pushButton_minus->setChecked(false);
    ui->pushButton_div->setChecked(false);
    ui->pushButton_multi->setChecked(false);

    ui->label->setText("0");
}


void calculator::on_pushButton_equal_clicked()
{
    double labelNumber, num_second;
    QString new_label;
    num_second = ui->label->text().toDouble();
    if(ui->pushButton_plus->isChecked()){
        labelNumber = num_first + num_second;
        new_label = QString::number(labelNumber);

        ui->label->setText(new_label);

        QVBoxLayout* layout = ui->layout;
        QLabel* newLabel = new QLabel(new_label);
        count = count + 1;
        newLabel->setObjectName(QString("label%1").arg(count));
        QCheckBox* check = new QCheckBox(tr("Сложение"));
        check->setObjectName(QString("check%1").arg(count));
        layout->addWidget(newLabel);
        layout->addWidget(check);

        ui->pushButton_plus->setChecked(false);
    } else if (ui->pushButton_minus->isChecked()){
        labelNumber = num_first - num_second;
        new_label = QString::number(labelNumber);

        ui->label->setText(new_label);

        QVBoxLayout* layout = ui->layout;
        QLabel* newLabel = new QLabel(new_label);
        count = count + 1;
        newLabel->setObjectName(QString("label%1").arg(count));
        QCheckBox* check = new QCheckBox(tr("Вычитание"));
        check->setObjectName(QString("check%1").arg(count));
        layout->addWidget(newLabel);
        layout->addWidget(check);

        ui->pushButton_minus->setChecked(false);
    } else if (ui->pushButton_div->isChecked()){
        if (num_second == 0){
            ui->label->setText("0");
        } else {
            labelNumber = num_first / num_second;
            new_label = QString::number(labelNumber);

            ui->label->setText(new_label);

            QVBoxLayout* layout = ui->layout;
            QLabel* newLabel = new QLabel(new_label);
            count = count + 1;
            newLabel->setObjectName(QString("label%1").arg(count));
            QCheckBox* check = new QCheckBox(tr("Деление"));
            check->setObjectName(QString("check%1").arg(count));
            layout->addWidget(newLabel);
            layout->addWidget(check);
        }
        ui->pushButton_div->setChecked(false);
    } else if (ui->pushButton_multi->isChecked()){
        labelNumber = num_first * num_second;
        new_label = QString::number(labelNumber);

        ui->label->setText(new_label);

        QVBoxLayout* layout = ui->layout;
        QLabel* newLabel = new QLabel(new_label);
        count = count + 1;
        newLabel->setObjectName(QString("label%1").arg(count));
        QCheckBox* check = new QCheckBox(tr("Умножение"));
        check->setObjectName(QString("check%1").arg(count));
        layout->addWidget(newLabel);
        layout->addWidget(check);

        ui->pushButton_multi->setChecked(false);
    }
}


void calculator::on_btn_clear_clicked()
{
    while (QLayoutItem* item = ui->layout->takeAt(0)) {
        delete item->widget();
        delete item;
    }
}


void calculator::on_btnMove_clicked()
{
    int index = ui->lineCount->text().toInt();
    QCheckBox *check = findChild<QCheckBox*>(QString("check%1").arg(index));
    if (check) { // Проверяем, что check не равен nullptr
        QLabel *lable = findChild<QLabel*>(QString("lable%1").arg(index));
        if (lable) { // Проверяем, что lable не равен nullptr
            if (check->isChecked()) {
                ui->label->setText(lable->text());
            }
        }
    }
}

