#ifndef TMATRIX_H
#define TMATRIX_H


#include <QVector>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>

using namespace std;

class TMatrix
{
private:
    QVector <QVector <double>> matrix;

    double det(double **M, int size); // вычисляет определитель матрицы
    static void * AlgebraicComplement (void* thread_data);
    void setMatrix(const int n); // перегруженная функция для ввода матрицы "вручную"
    void setMatrix(const char *fname, const int n); // перегруженная функция для ввода матрицы из файла
    void getMatrix(); // перегруженная функция вывода матрицы на экран
    void getMatrix(const char *fname); //перегруженная функция для вывода матрицы в файл

    //специальная структура для данных потока
    typedef struct{
        int row_index; //номер обрабатываемой строки
        int col_index; // номер обрабатываемого элемента
        int size; //размер исходной матрицы
        //указатели на матрицы
        double** copy;
    } pthrData;

public:

    /*QVector <QVector <double>> matrix;
    double det(double **M, int size);*/

    bool MThReverse(int size);
    bool Reverse (int size); // осуществляет поиск обратной
    void InitMatrix(const int n);
    void ShowMatrix();

};

#endif // TMATRIX_H
