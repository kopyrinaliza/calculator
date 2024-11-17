#include "matrix.h"
#include "ui_matrix.h"
#include <QMessageBox>
#include <QCheckBox>

matrix::matrix(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::matrix)
{
    ui->setupUi(this);

    connect(ui->btnCol_plus1, SIGNAL(clicked()), this, SLOT(countColPlus1()));
    connect(ui->btnCol_min1, SIGNAL(clicked()), this, SLOT(countColMin1()));
    connect(ui->btnRow_plus1, SIGNAL(clicked()), this, SLOT(countRowPlus1()));
    connect(ui->btnRow_min1, SIGNAL(clicked()), this, SLOT(countRowMin1()));
    connect(ui->btnCol_plus2, SIGNAL(clicked()), this, SLOT(countColPlus2()));
    connect(ui->btnCol_min2, SIGNAL(clicked()), this, SLOT(countColMin2()));
    connect(ui->btnRow_plus2, SIGNAL(clicked()), this, SLOT(countRowPlus2()));
    connect(ui->btnRow_min2, SIGNAL(clicked()), this, SLOT(countRowMin2()));
    connect(ui->btn_chisloA, SIGNAL(clicked()), this, SLOT(multi_chisloA()));
    connect(ui->btnAdd, SIGNAL(clicked()), this, SLOT(matr_add()));
    connect(ui->btnDeduc, SIGNAL(clicked()), this, SLOT(matr_minus()));
    connect(ui->btnMulti, SIGNAL(clicked()), this, SLOT(matr_multi()));
    connect(ui->btnMinor, SIGNAL(clicked()), this, SLOT(matr_minor()));
    connect(ui->btnTrans, SIGNAL(clicked()), this, SLOT(matr_trans()));
    connect(ui->btnDet, SIGNAL(clicked()), this, SLOT(matr_det()));
    connect(ui->btnMinorDet, SIGNAL(clicked()), this, SLOT(min_det()));
    connect(ui->btn_inv, SIGNAL(clicked()), this, SLOT(matr_inv()));
    connect(ui->btnAlgDop, SIGNAL(clicked()), this, SLOT(matr_cof()));
    connect(ui->btnAlg, SIGNAL(clicked()), this, SLOT(alg_dop()));
    connect(ui->btnSolve, SIGNAL(clicked()), this, SLOT(solve_equ()));
    connect(ui->btn_minorElem, SIGNAL(clicked()), this, SLOT(min_elem()));
    connect(ui->btn_chistka, SIGNAL(clicked()), this, SLOT(ochistka()));
    connect(ui->btnMoveA, SIGNAL(clicked()), this, SLOT(move_A()));
}

matrix::~matrix()
{
    delete ui;
}

void matrix::countColPlus1(){
    cols = cols + 1;
    ui->table_1->setColumnCount(cols);
}

void matrix::countColMin1(){
    cols = cols - 1;
    ui->table_1->setColumnCount(cols);
}

void matrix::countRowPlus1(){
    rows = rows + 1;
    ui->table_1->setRowCount(rows);
}

void matrix::countRowMin1(){
    rows = rows - 1;
    ui->table_1->setRowCount(rows);
}

void matrix::countColPlus2(){
    cols2 = cols2 + 1;
    ui->table_2->setColumnCount(cols2);
}

void matrix::countColMin2(){
    cols2 = cols2 - 1;
    ui->table_2->setColumnCount(cols2);
}

void matrix::countRowPlus2(){
    rows2 = rows2 + 1;
    ui->table_2->setRowCount(rows2);
}

void matrix::countRowMin2(){
    rows2 = rows2 - 1;
    ui->table_2->setRowCount(rows2);
}

void matrix::multi_chisloA(){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            QTableWidgetItem *item = ui->table_1->item(i, j);
            QString temp = item->text();
            int n = ui->lineChislo->text().toInt();
            int mult_chislo = temp.toInt() * n;
            QString s = QString::number(mult_chislo);
            ui->table_1->setItem(i,j,new QTableWidgetItem(s));
        }
    }

    QTableWidget *table = new QTableWidget(rows,cols);

    table->verticalHeader()->hide();
    table->horizontalHeader()->hide();
    for(int i = 0; i < rows; ++i){
        for (int j = 0; j < cols; ++j){
            table->setItem(i,j,new QTableWidgetItem(ui->table_1->item(i,j)->text()));
        }
    }
    QVBoxLayout *layout = ui->layout;
    layout->addWidget(table);
    count = count + 1;
    table->setObjectName(QString("table%1").arg(count));
    QCheckBox *check = new QCheckBox(tr("Умножение на число"));
    check->setObjectName(QString("check%1").arg(count));
    layout->addWidget(check);
}

void matrix::move_A(){
    int index = ui->lineMove->text().toInt();
    QCheckBox *check = findChild<QCheckBox*>(QString("check%1").arg(index));
    if(check->isChecked()){
        QTableWidget *table = findChild<QTableWidget*>(QString("table%1").arg(index));
        ui->table_1->setRowCount(table->rowCount());
        ui->table_1->setColumnCount(table->columnCount());
        for(int i = 0; i < table->rowCount(); ++i){
            for (int j = 0; j < table->columnCount(); ++j){
                ui->table_1->setItem(i,j, new QTableWidgetItem(table->item(i,j)->text()));
            }
        }
    }
}

void matrix::matr_add(){
    try {
        if (rows != rows2 || cols != cols2) {
            throw std::runtime_error("Количество строк и/или столбцов в таблицах не совпадает");
        }

        ui->table_3->setRowCount(rows);
        ui->table_3->setColumnCount(cols);

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                QTableWidgetItem* item1 = ui->table_1->item(i, j);
                QTableWidgetItem* item2 = ui->table_2->item(i, j);

                bool ok1, ok2;
                int value1 = item1->text().toInt(&ok1);
                int value2 = item2->text().toInt(&ok2);

                if (!ok1 || !ok2) {
                    throw std::runtime_error("Некорректные данные в одной из ячеек");
                }

                int sum = value1 + value2;
                QString result = QString::number(sum);
                ui->table_3->setItem(i, j, new QTableWidgetItem(result));
            }
        }
    }
    catch (const std::exception& e) {
        QMessageBox::critical(this, "Ошибка!", QString::fromStdString(e.what()));
    }
    QTableWidget *table = new QTableWidget(rows,cols);

    table->verticalHeader()->hide();
    table->horizontalHeader()->hide();
    for(int i = 0; i < rows; ++i){
        for (int j = 0; j < cols; ++j){
            table->setItem(i,j,new QTableWidgetItem(ui->table_3->item(i,j)->text()));
        }
    }
    QVBoxLayout *layout = ui->layout;
    layout->addWidget(table);
    count = count + 1;
    table->setObjectName(QString("table%1").arg(count));
    QCheckBox *check = new QCheckBox(tr("Сложение"));
    check->setObjectName(QString("check%1").arg(count));
    layout->addWidget(check);


}

void matrix::matr_minus(){
    try {
        if (rows != rows2 || cols != cols2) {
            throw std::runtime_error("Количество строк и/или столбцов в таблицах не совпадает");
        }

        ui->table_3->setRowCount(rows);
        ui->table_3->setColumnCount(cols);

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                QTableWidgetItem* item1 = ui->table_1->item(i, j);
                QTableWidgetItem* item2 = ui->table_2->item(i, j);

                bool ok1, ok2;
                int value1 = item1->text().toInt(&ok1);
                int value2 = item2->text().toInt(&ok2);

                if (!ok1 || !ok2) {
                    throw std::runtime_error("Некорректные данные в одной из ячеек");
                }

                int min = value1 - value2;
                QString result = QString::number(min);
                ui->table_3->setItem(i, j, new QTableWidgetItem(result));
            }
        }
    }
    catch (const std::exception& e) {
        QMessageBox::critical(this, "Ошибка!", QString::fromStdString(e.what()));
    }

    QTableWidget *table = new QTableWidget(rows,cols);
    table->verticalHeader()->hide();
    table->horizontalHeader()->hide();
    for(int i = 0; i < rows; ++i){
        for (int j = 0; j < cols; ++j){
            table->setItem(i,j,new QTableWidgetItem(ui->table_3->item(i,j)->text()));
        }
    }
    QVBoxLayout *layout = ui->layout;
    layout->addWidget(table);
    count = count + 1;
    table->setObjectName(QString("table%1").arg(count));
    QCheckBox *check = new QCheckBox(tr("Вычитание"));
    check->setObjectName(QString("check%1").arg(count));
    layout->addWidget(check);
}

void matrix::matr_multi(){
    if (cols != rows2) {
        throw std::runtime_error("Количество строк и/или столбцов в таблицах не совпадает");
    }

    QVector<QVector<int>> matrix1(rows, QVector<int>(cols));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            QTableWidgetItem* item = ui->table_1->item(i, j);
            if (item) {
                bool ok;
                int value = item->text().toInt(&ok);
                if (ok) {
                    matrix1[i][j] = value;
                } else {
                    QMessageBox::warning(this, "Ошибка", "Некорректные данные в таблице 1!");
                    return;
                }
            } else {
                QMessageBox::warning(this, "Ошибка", "Пустая ячейка в таблице 1!");
                return;
            }
        }
    }

    // Получаем данные из второй таблицы
    QVector<QVector<int>> matrix2(rows2, QVector<int>(cols2));
    for (int i = 0; i < rows2; ++i) {
        for (int j = 0; j < cols2; ++j) {
            QTableWidgetItem* item = ui->table_2->item(i, j);
            if (item) {
                bool ok;
                int value = item->text().toInt(&ok);
                if (ok) {
                    matrix2[i][j] = value;
                } else {
                    QMessageBox::warning(this, "Ошибка", "Некорректные данные в таблице 2!");
                    return;
                }
            } else {
                QMessageBox::warning(this, "Ошибка", "Пустая ячейка в таблице 2!");
                return;
            }
        }
    }

    // Умножаем матрицы
    QVector<QVector<int>> resultMatrix(rows, QVector<int>(cols2));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols2; ++j) {
            int sum = 0;
            for (int k = 0; k < cols; ++k) {
                sum += matrix1[i][k] * matrix2[k][j];
            }
            resultMatrix[i][j] = sum;
        }
    }

    // Заполняем результирующую таблицу
    ui->table_3->setRowCount(rows);
    ui->table_3->setColumnCount(cols2);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols2; ++j) {
            QString result = QString::number(resultMatrix[i][j]);
            ui->table_3->setItem(i, j, new QTableWidgetItem(result));
        }
    }

    QTableWidget *table = new QTableWidget(rows,cols2);
    table->verticalHeader()->hide();
    table->horizontalHeader()->hide();
    for(int i = 0; i < rows; ++i){
        for (int j = 0; j < cols2; ++j){
            table->setItem(i,j,new QTableWidgetItem(ui->table_3->item(i,j)->text()));
        }
    }
    QVBoxLayout *layout = ui->layout;
    layout->addWidget(table);
    count = count + 1;
    table->setObjectName(QString("table%1").arg(count));
    QCheckBox *check = new QCheckBox(tr("Умножение матриц"));
    check->setObjectName(QString("check%1").arg(count));
    layout->addWidget(check);
}

void matrix::matr_minor(){
    int r = ui->lineRow->text().toInt();
    int c = ui->lineCol->text().toInt();

    QVector<QString> minorElems;
    for (int i = 0; i < rows; i++) {
        if (i == r-1) continue;
        for  (int j = 0; j < cols; j++){
            if (j == c-1) continue;
            QTableWidgetItem* item1 = ui->table_1->item(i,j);
            QString s =item1->text();
            minorElems.push_back(s);
        }
    }
    int m = 0;
    for (int i = 0; i < rows-1; i++){
        for (int j = 0; j < cols-1; j++){
            QString k = minorElems[m];
            ui->table_3->setItem(i,j, new QTableWidgetItem(k));
            m++;
        }
    }

    QTableWidget *table = new QTableWidget(rows-1,cols-1);
    table->verticalHeader()->hide();
    table->horizontalHeader()->hide();
    for(int i = 0; i < rows-1; ++i){
        for (int j = 0; j < cols-1; ++j){
            table->setItem(i,j,new QTableWidgetItem(ui->table_3->item(i,j)->text()));
        }
    }
    QVBoxLayout *layout = ui->layout;
    layout->addWidget(table);
    count = count + 1;
    table->setObjectName(QString("table%1").arg(count));
    QCheckBox *check = new QCheckBox(tr("Минор матрицы"));
    check->setObjectName(QString("check%1").arg(count));
    layout->addWidget(check);
}

void matrix::matr_trans(){
    ui->table_3->setRowCount(cols);
    ui->table_3->setColumnCount(rows);
    for (int i = 0; i < cols; i++){
        for (int j = 0; j < rows; j++){
            ui->table_3->setItem(i,j,new QTableWidgetItem(ui->table_1->item(j,i)->text()));
        }
    }
    QTableWidget *table = new QTableWidget(cols,rows);
    table->verticalHeader()->hide();
    table->horizontalHeader()->hide();
    for(int i = 0; i < cols; ++i){
        for (int j = 0; j < rows; ++j){
            table->setItem(i,j,new QTableWidgetItem(ui->table_3->item(i,j)->text()));
        }
    }
    QVBoxLayout *layout = ui->layout;
    layout->addWidget(table);
    count = count + 1;
    table->setObjectName(QString("table%1").arg(count));
    QCheckBox *check = new QCheckBox(tr("Транспонирование"));
    check->setObjectName(QString("check%1").arg(count));
    layout->addWidget(check);
}

void matrix::matr_det(){
    int size = ui->table_1->rowCount();

    if (size != ui->table_1->columnCount()) {
            QMessageBox::warning(this, "Ошибка", "Матрица должна быть квадратной!");
            return;
        }

        // Получаем данные из таблицы
        QVector<QVector<double>> matrix(size, QVector<double>(size));
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                QTableWidgetItem* item = ui->table_1->item(i, j);
                if (item) {
                    bool ok;
                    double value = item->text().toDouble(&ok);
                    if (ok) {
                        matrix[i][j] = value;
                    } else {
                        QMessageBox::warning(this, "Ошибка", "Некорректные данные в таблице!");
                        return;
                    }
                } else {
                    QMessageBox::warning(this, "Ошибка", "Пустая ячейка в таблице!");
                    return;
                }
            }
        }

        // Вычисляем определитель
        double det = determinant(matrix);

        // Показываем результат
        ui->lineDet->setText(QString::number(det));

        QTableWidget *table = new QTableWidget(1,1);
        table->verticalHeader()->hide();
        table->horizontalHeader()->hide();
        for(int i = 0; i < 1; ++i){
            for (int j = 0; j < 1; ++j){
                table->setItem(i,j,new QTableWidgetItem(QString::number(det)));
            }
        }
        QVBoxLayout *layout = ui->layout;
        layout->addWidget(table);
        count = count + 1;
        table->setObjectName(QString("table%1").arg(count));
        QCheckBox *check = new QCheckBox(tr("Определитель"));
        check->setObjectName(QString("check%1").arg(count));
        layout->addWidget(check);
}

void matrix::min_det(){
    int size = ui->table_1->rowCount();

    if (size != ui->table_1->columnCount()) {
        QMessageBox::warning(this, "Ошибка", "Матрица должна быть квадратной!");
        return;
    }

    // Получаем данные из таблицы
    QVector<QVector<double>> matrix(size, QVector<double>(size));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            QTableWidgetItem* item = ui->table_1->item(i, j);
            if (item) {
                bool ok;
                double value = item->text().toDouble(&ok);
                if (ok) {
                    matrix[i][j] = value;
                } else {
                    QMessageBox::warning(this, "Ошибка", "Некорректные данные в таблице!");
                    return;
                }
            } else {
                QMessageBox::warning(this, "Ошибка", "Пустая ячейка в таблице!");
                return;
            }
        }
    }

    // Индекс элемента для которого считаем минор
    int rowIndex = ui->rowSpinBox->value();
    int colIndex = ui->colSpinBox->value();

    if (rowIndex >= size || colIndex >= size) {
        QMessageBox::warning(this, "Ошибка", "Индекс выходит за пределы матрицы!");
        return;
    }

    // Вычисляем минорный определитель
    double minorDet = minorDeterminant(matrix, rowIndex, colIndex);

    // Показываем результат
    ui->lineMinDet->setText(QString::number(minorDet));

    QTableWidget *table = new QTableWidget(1,1);
    table->verticalHeader()->hide();
    table->horizontalHeader()->hide();
    for(int i = 0; i < 1; ++i){
        for (int j = 0; j < 1; ++j){
            table->setItem(i,j,new QTableWidgetItem(QString::number(minorDet)));
        }
    }
    QVBoxLayout *layout = ui->layout;
    layout->addWidget(table);
    count = count + 1;
    table->setObjectName(QString("table%1").arg(count));
    QCheckBox *check = new QCheckBox(tr("Определитель минора"));
    check->setObjectName(QString("check%1").arg(count));
    layout->addWidget(check);
}

void matrix::matr_inv(){
    int size = ui->table_1->rowCount();

    if (size != ui->table_1->columnCount()) {
        QMessageBox::warning(this, "Ошибка", "Матрица должна быть квадратной!");
        return;
    }

    // Получаем данные из таблицы
    QVector<QVector<double>> inputMatrix(size, QVector<double>(size));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            QTableWidgetItem* item = ui->table_1->item(i, j);
            if (item) {
                bool ok;
                double value = item->text().toDouble(&ok);
                if (ok) {
                    inputMatrix[i][j] = value;
                } else {
                    QMessageBox::warning(this, "Ошибка", "Некорректные данные в таблице!");
                    return;
                }
            } else {
                QMessageBox::warning(this, "Ошибка", "Пустая ячейка в таблице!");
                return;
            }
        }
    }

    // Вычисляем обратную матрицу
    QVector<QVector<double>> outputMatrix(size, QVector<double>(size));
    inverseMatrix(inputMatrix, outputMatrix);

    // Заполняем результирующую таблицу
    ui->table_3->setRowCount(size);
    ui->table_3->setColumnCount(size);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            QString result = QString::number(outputMatrix[i][j], 'f', 6); // Округляем до 6 знаков после запятой
            ui->table_3->setItem(i, j, new QTableWidgetItem(result));
        }
    }

    QTableWidget *table = new QTableWidget(size,size);
    table->verticalHeader()->hide();
    table->horizontalHeader()->hide();
    for(int i = 0; i < size; ++i){
        for (int j = 0; j < size; ++j){
            table->setItem(i,j,new QTableWidgetItem(ui->table_3->item(i,j)->text()));
        }
    }
    QVBoxLayout *layout = ui->layout;
    layout->addWidget(table);
    count = count + 1;
    table->setObjectName(QString("table%1").arg(count));
    QCheckBox *check = new QCheckBox(tr("Обратная матрица"));
    check->setObjectName(QString("check%1").arg(count));
    layout->addWidget(check);
}

void matrix::matr_cof(){
    int size = ui->table_1->rowCount();

    ui->table_3->setColumnCount(size);
    ui->table_3->setRowCount(size);

    QVector<QVector<double>> matrix(size, QVector<double>(size));

    // Читаем значения из таблицы
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = ui->table_1->item(i, j)->text().toDouble();
        }
    }

    QVector<QVector<double>> cofactorMatrix = computeCofactorMatrix(matrix);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            ui->table_3->setItem(i, j, new QTableWidgetItem(QString::number(cofactorMatrix[i][j])));
        }
    }
    QTableWidget *table = new QTableWidget(size,size);
    table->verticalHeader()->hide();
    table->horizontalHeader()->hide();
    for(int i = 0; i < size; ++i){
        for (int j = 0; j < size; ++j){
            table->setItem(i,j,new QTableWidgetItem(ui->table_3->item(i,j)->text()));
        }
    }
    QVBoxLayout *layout = ui->layout;
    layout->addWidget(table);
    count = count + 1;
    table->setObjectName(QString("table%1").arg(count));
    QCheckBox *check = new QCheckBox(tr("Матрица алгебраических дополнений"));
    check->setObjectName(QString("check%1").arg(count));
    layout->addWidget(check);
}

void matrix::alg_dop(){
    int currentRow = ui->rowSpinBox_2->value();
    int currentCol = ui->colSpinBox_2->value();

    int size = ui->table_1->rowCount();
    QVector<QVector<double>> matrix(size, QVector<double>(size));

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = ui->table_1->item(i, j)->text().toDouble();
        }
    }

    QVector<QVector<double>> minor(size - 1, QVector<double>(size - 1));
    for (int i = 0, row = 0; i < size; ++i) {
        if (i != currentRow) {
            for (int j = 0, col = 0; j < size; ++j) {
                if (j != currentCol) {
                    minor[row][col++] = matrix[i][j];
                }
            }
            ++row;
        }
    }

    double det = determinant(minor);

    double cofactor = ((currentRow + currentCol) % 2 == 0 ? 1 : -1) * det;

    ui->lineAlgDop->setText(QString::number(cofactor));

    QTableWidget *table = new QTableWidget(1,1);
    table->verticalHeader()->hide();
    table->horizontalHeader()->hide();
    for(int i = 0; i < 1; ++i){
        for (int j = 0; j < 1; ++j){
            table->setItem(i,j,new QTableWidgetItem(QString::number(cofactor)));
        }
    }
    QVBoxLayout *layout = ui->layout;
    layout->addWidget(table);
    count = count + 1;
    table->setObjectName(QString("table%1").arg(count));
    QCheckBox *check = new QCheckBox(tr("Алгебраический определитель"));
    check->setObjectName(QString("check%1").arg(count));
    layout->addWidget(check);
}

void matrix::solve_equ(){
    int size = ui->table_1->rowCount();

    if (size != ui->table_1->columnCount()) {
        QMessageBox::warning(this, "Ошибка", "Матрица должна быть квадратной!");
        return;
    }

    // Получаем данные из таблицы
    QVector<QVector<double>> inputMatrix(size, QVector<double>(size));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            QTableWidgetItem* item = ui->table_1->item(i, j);
            if (item) {
                bool ok;
                double value = item->text().toDouble(&ok);
                if (ok) {
                    inputMatrix[i][j] = value;
                } else {
                    QMessageBox::warning(this, "Ошибка", "Некорректные данные в таблице!");
                    return;
                }
            } else {
                QMessageBox::warning(this, "Ошибка", "Пустая ячейка в таблице!");
                return;
            }
        }
    }

    // Вычисляем обратную матрицу
    QVector<QVector<double>> outputMatrix(size, QVector<double>(size));
    inverseMatrix(inputMatrix, outputMatrix);

    QVector<QVector<double>> matrixB(size, QVector<double>(size));
    for(int i = 0; i < rows2; ++i){
        for (int j = 0; j < cols2; ++j){
            matrixB[i][j] = ui->table_2->item(i,j)->text().toDouble();
        }
    }

    QVector<QVector<double>> resultMatrix(cols, QVector<double>(cols2));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < cols2; ++j) {
            double sum = 0;
            for (int k = 0; k < size; ++k) {
                sum += matrixB[i][k] * outputMatrix[k][j];
            }
            resultMatrix[i][j] = sum;
        }
    }
    ui->table_3->setRowCount(cols);
    ui->table_3->setColumnCount(cols2);
    // Заполним результирующую таблицу значениями
    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < cols2; ++j) {
            QString result = QString::number(resultMatrix[i][j], 'f', 6); // Округляем до 6 знаков после запятой
            ui->table_3->setItem(i, j, new QTableWidgetItem(result));
        }
    }

    QTableWidget *table = new QTableWidget(cols2,cols2);
    table->verticalHeader()->hide();
    table->horizontalHeader()->hide();
    for(int i = 0; i < cols2; ++i){
        for (int j = 0; j < cols2; ++j){
            table->setItem(i,j,new QTableWidgetItem(ui->table_3->item(i,j)->text()));
        }
    }
    QVBoxLayout *layout = ui->layout;
    layout->addWidget(table);
    count = count + 1;
    table->setObjectName(QString("table%1").arg(count));
    QCheckBox *check = new QCheckBox(tr("Решение AX = B"));
    check->setObjectName(QString("check%1").arg(count));
    layout->addWidget(check);
}

void matrix::min_elem(){
    int size = ui->table_1->rowCount();
    QVector<QVector<double>> matrix(size, QVector<double>(size));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            QTableWidgetItem* item = ui->table_1->item(i, j);
            if (item) {
                bool ok;
                double value = item->text().toDouble(&ok);
                if (ok) {
                    matrix[i][j] = value;
                } else {
                    QMessageBox::warning(this, "Ошибка", "Некорректные данные в таблице!");
                    return;
                }
            } else {
                QMessageBox::warning(this, "Ошибка", "Пустая ячейка в таблице!");
                return;
            }
        }
    }
    ui->table_3->setRowCount(size);
    ui->table_3->setColumnCount(size);
    for (int i = 0; i < rows; ++i){
        for (int j = 0; j < cols; ++j){
            int minorValue = minorDeterminant(matrix, i, j);
            ui->table_3->setItem(i,j,new QTableWidgetItem(QString::number(minorValue)));
        }
    }

    QTableWidget *table = new QTableWidget(rows,cols);
    table->verticalHeader()->hide();
    table->horizontalHeader()->hide();
    for(int i = 0; i < rows; ++i){
        for (int j = 0; j < cols; ++j){
            table->setItem(i,j,new QTableWidgetItem(ui->table_3->item(i,j)->text()));
        }
    }
    QVBoxLayout *layout = ui->layout;
    layout->addWidget(table);
    count = count + 1;
    table->setObjectName(QString("table%1").arg(count));
    QCheckBox *check = new QCheckBox(tr("Матрицы минора для соответствующих элементам и их индексу"));
    check->setObjectName(QString("check%1").arg(count));
    layout->addWidget(check);
}

void  matrix::ochistka(){
    while (QLayoutItem* item = ui->layout->takeAt(0)) {
        delete item->widget();
        delete item;
    }
}










