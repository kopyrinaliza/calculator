#ifndef MATRIX_H
#define MATRIX_H

#include <QMainWindow>
#include <QMessageBox>

namespace Ui {
class matrix;
}

class matrix : public QMainWindow
{
    Q_OBJECT

public:
    explicit matrix(QWidget *parent = nullptr);
    ~matrix();

    int rows = 0;
    int cols = 0;
    int rows2 = 0;
    int cols2 = 0;
    int count = 0;
    double determinant(const QVector<QVector<double>>& matrix)
    {
        int size = matrix.size();
        double det = 0.0;

        if (size == 1) {
            return matrix[0][0]; // Определитель матрицы 1x1 равен её единственному элементу
        } else if (size == 2) {
            // Формула для определителя матрицы 2x2
            return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
        } else {
            // Рекурсия для больших матриц
            for (int col = 0; col < size; ++col) {
                // Создаем подматрицу, удаляя первую строку и текущий столбец
                QVector<QVector<double>> subMatrix(size - 1, QVector<double>(size - 1));
                for (int row = 1; row < size; ++row) {
                    int currentCol = 0;
                    for (int innerCol = 0; innerCol < size; ++innerCol) {
                        if (innerCol != col) {
                            subMatrix[row - 1][currentCol++] = matrix[row][innerCol];
                        }
                    }
                }

                // Рекурсивный вызов для подматрицы
                det += ((col % 2 == 0) ? 1 : -1) * matrix[0][col] * determinant(subMatrix);
            }
        }

        return det;
    }

    double minorDeterminant(const QVector<QVector<double>>& matrix, int rowIndex, int colIndex)
    {
        int size = matrix.size();
        QVector<QVector<double>> minorMatrix(size - 1, QVector<double>(size - 1));

        for (int i = 0, minorI = 0; i < size; ++i) {
            if (i == rowIndex) continue;
            for (int j = 0, minorJ = 0; j < size; ++j) {
                if (j == colIndex) continue;
                minorMatrix[minorI][minorJ++] = matrix[i][j];
            }
            minorI++;
        }

        return determinant(minorMatrix);
    }
    void inverseMatrix(const QVector<QVector<double>>& inputMatrix, QVector<QVector<double>>& outputMatrix)
    {
        int size = inputMatrix.size();
        QVector<QVector<double>> augmentedMatrix(size, QVector<double>(2 * size)); // Объединенная матрица

        // Копируем исходную матрицу в левую половину объединенной матрицы
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                augmentedMatrix[i][j] = inputMatrix[i][j];
            }
        }

        // Формируем правую половину объединенной матрицы как единичную матрицу
        for (int i = 0; i < size; ++i) {
            for (int j = size; j < 2 * size; ++j) {
                augmentedMatrix[i][j] = (i == j - size) ? 1.0 : 0.0;
            }
        }

        // Приводим объединенную матрицу к виду, когда левая половина становится единичной
        for (int col = 0; col < size; ++col) {
            // Находим ненулевой элемент в текущем столбце
            int pivotRow = col;
            while (pivotRow < size && fabs(augmentedMatrix[pivotRow][col]) < 1e-9) {
                pivotRow++;
            }

            if (pivotRow == size) {
                QMessageBox::warning(nullptr, "Ошибка", "Матрица необратима!");
                return;
            }

            // Меняем местами текущую строку и строку с найденным ненулевым элементом
            if (pivotRow != col) {
                for (int j = 0; j < 2 * size; ++j) {
                    std::swap(augmentedMatrix[col][j], augmentedMatrix[pivotRow][j]);
                }
            }

            // Делим текущую строку на ведущий элемент
            double pivotValue = augmentedMatrix[col][col];
            for (int j = 0; j < 2 * size; ++j) {
                augmentedMatrix[col][j] /= pivotValue;
            }

            // Приводим остальные строки к нулю в текущем столбце
            for (int row = 0; row < size; ++row) {
                if (row != col) {
                    double factor = augmentedMatrix[row][col];
                    for (int j = 0; j < 2 * size; ++j) {
                        augmentedMatrix[row][j] -= factor * augmentedMatrix[col][j];
                    }
                }
            }
        }

        // Копируем правую половину объединенной матрицы в выходную матрицу
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                outputMatrix[i][j] = augmentedMatrix[i][j + size];
            }
        }
    }

    QVector<QVector<double>> computeCofactorMatrix(const QVector<QVector<double>>& matrix)
    {
        int n = matrix.size();
        QVector<QVector<double>> result(n, QVector<double>(n));

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                // Создаем подматрицу, исключая строку i и столбец j
                QVector<QVector<double>> submatrix(n - 1, QVector<double>(n - 1));
                for (int k = 0, row = 0; k < n; ++k) {
                    if (k != i) {
                        for (int l = 0, col = 0; l < n; ++l) {
                            if (l != j) {
                                submatrix[row][col++] = matrix[k][l];
                            }
                        }
                        ++row;
                    }
                }

                // Вычисляем определитель подматрицы
                double det = determinant(submatrix);

                // Присваиваем значение в результирующую матрицу с учетом знака
                result[i][j] = ((i + j) % 2 == 0 ? 1 : -1) * det;
            }
        }

        return result;
    }


private:
    Ui::matrix *ui;
private slots:
    void countColPlus1();
    void countColMin1();
    void countRowPlus1();
    void countRowMin1();
    void countColPlus2();
    void countColMin2();
    void countRowPlus2();
    void countRowMin2();
    void multi_chisloA();
    void matr_add();
    void matr_minus();
    void matr_multi();
    void matr_minor();
    void matr_trans();
    void matr_det();
    void min_det();
    void matr_inv();
    void matr_cof();
    void alg_dop();
    void solve_equ();
    void min_elem();
    void ochistka();
    void move_A();
};

#endif // MATRIX_H
