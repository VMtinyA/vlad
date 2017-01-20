#include <QCoreApplication>
#include "tmatrix.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int n;
    printf("Enter n\n");
    scanf("%i", &n);

    TMatrix *Matrix = new TMatrix();

    Matrix->InitMatrix(n);

    /*double **copy = new double *[n]();
        // Заполняем копию исходной матрицы
    for (int i = 0; i < n; ++i)
    {
        copy[i] = new double [n];
        for (int j = 0; j < n; ++j)
            copy[i][j] = Matrix->matrix[i][j];
    }
    printf("Det = %.3f\n", Matrix->det(copy, n));*/

    while (!Matrix->Reverse(n))
        {
            printf("Error\n");
            Matrix->InitMatrix(n);
        }
    Matrix->MThReverse(n);
    Matrix->ShowMatrix();

    delete Matrix;

    /*printf("Для продолжения нажмите Enter\n");
    while (getc(stdin) != '\n');*/
    exit(0);

    return a.exec();
}
