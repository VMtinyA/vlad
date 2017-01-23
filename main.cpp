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

    while (!Matrix->Reverse(n))
        {
            printf("Error\n");
            Matrix->InitMatrix(n);
        }
    Matrix->ShowMatrix();

    delete Matrix;

    /*printf("Для продолжения нажмите Enter\n");
    while (getc(stdin) != '\n');*/
    exit(0);

    return a.exec();
}
