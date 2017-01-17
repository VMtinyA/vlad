/* Класс TMatrix предназначен для работы с квадратной матрицей размера n
 * хранение матрицы в виде "вектор векторов"
 * в классе матрицы содержатся функции для ее преобразования,
 * а также функции ее ввода-вывода на экран / в файл
 * */

#include "tmatrix.h"

#define LEN 128
#define ERROR_OPEN_FILE -3

using namespace std;

/*double TMatrix::Det( const QVector <QVector <double>> matrix ) // вычисление det рекурсивным методом разложения по строке
{
dick

}*/

bool TMatrix::Reverse(int size)
{
    // Функция, производящая обращение матрицы.
        // Принимает:
        //     size   - размерность матрицы
        // Возвращает:
        //     true в случае успешного обращения, false в противном случае

        // Изначально результирующая матрица является единичной
        // Заполняем единичную матрицу
    double **E = new double *[size]();

    for (int i = 0; i < size; ++i)
        {
            E[i] = new double [size];
            for (int j = 0; j < size; ++j)
                E[i][j] = 0;

            E[i][i] = 1;
        }

        // Копия исходной матрицы
    double **copy = new double *[size]();

        // Заполняем копию исходной матрицы
    for (int i = 0; i < size; ++i)
    {
        copy[i] = new double [size];
        for (int j = 0; j < size; ++j)
            copy[i][j] = this->matrix[i][j];
    }

        // Проходим по строкам матрицы (назовём их исходными)
        // сверху вниз. На данном этапе происходит прямой ход
        // и исходная матрица превращается в верхнюю треугольную
    for (int k = 0; k < size; ++k)
    {
            // Если элемент на главной диагонали в исходной
            // строке - нуль, то ищем строку, где элемент
            // того же столбца не нулевой, и меняем строки
            // местами
         if (copy[k][k] == 0)
         {
                // Ключ, говорязий о том, что был произведён обмен строк
             bool changed = false;

                // Идём по строкам, расположенным ниже исходной
             for (int i = k + 1; i < size; ++i)
             {
                    // Если нашли строку, где в том же столбце
                    // имеется ненулевой элемент
                 if (copy[i][k] != 0)
                 {
                        // Меняем найденную и исходную строки местами
                        // как в исходной матрице, так и в единичной
                     swap(copy[k], copy[i]);
                     swap(E[k], E[i]);
                        // Взводим ключ - сообщаем о произведённом обмене строк
                     changed = true;
                     break;
                 }
             }

                // Если обмен строк произведён не был - матрица не может быть
                // обращена
             if (!changed)
             {
                    // Чистим память
                 for (int i = 0; i < size; ++i)
                    delete [] copy[i];
                 delete [] copy;

                 for (int i = 0; i < size; ++i)
                     delete [] E[i];
                 delete [] E;
                    // Сообщаем о неудаче обращения
                 return false;
             }
         }

            // Запоминаем делитель - диагональный элемент
         double div = copy[k][k];

            // Все элементы исходной строки делим на диагональный
            // элемент как в исходной матрице, так и в единичной
         for (int j = 0; j < size; ++j)
         {
             copy[k][j]   /= div;
             E[k][j] /= div;
         }

            // Идём по строкам, которые расположены ниже исходной
         for (int i = k + 1; i < size; ++i)
         {
                // Запоминаем множитель - элемент очередной строки,
                // расположенный под диагональным элементом исходной
                // строки
             double multi = copy[i][k];

                // Отнимаем от очередной строки исходную, умноженную
                // на сохранённый ранее множитель как в исходной,
                // так и в единичной матрице
             for (int j = 0; j < size; ++j)
             {
                 copy[i][j]   -= multi * copy[k][j];
                 E[i][j] -= multi * E[k][j];
             }
         }
     }

        // Проходим по верхней треугольной матрице, полученной
        // на прямом ходе, снизу вверх
        // На данном этапе происходит обратный ход, и из исходной
        // матрицы окончательно формируется единичная, а из единичной -
        // обратная
     for (int k = size - 1; k > 0; --k)
     {
            // Идём по строкам, которые расположены выше исходной
         for (int i = k - 1; i + 1 > 0; --i)
         {
                // Запоминаем множитель - элемент очередной строки,
                // расположенный над диагональным элементом исходной
                // строки
             double multi = copy[i][k];

                // Отнимаем от очередной строки исходную, умноженную
                // на сохранённый ранее множитель как в исходной,
                // так и в единичной матрице
             for (int j = 0; j < size; ++j)
             {
                 copy[i][j]   -= multi * copy[k][j];
                 E[i][j] -= multi * E[k][j];
             }
         }
     }

     for (int i = 0; i < size; ++i)
         for (int j = 0; j < size; ++j)
             this->matrix[i][j] = E[i][j];

        // Чистим память
     for (int i = 0; i < size; ++i)
         delete [] copy[i];

     delete [] copy;

     for (int i = 0; i < size; ++i)
         delete [] E[i];

     delete [] E;

        // Сообщаем об успехе обращения
     printf("Reversed\n");
     return true;
}

void TMatrix::setMatrix(const int n) // ввод вручную
{
    this->matrix.resize(n);
    for (int i = 0; i < (this->matrix.size()); i++)
        {
            this->matrix [i].resize (n);
            printf("Enter %i row\n", (i + 1));
            for (int j = 0; j < (this->matrix.size()); j++)
                {
                printf("Enter %i element\n", (j + 1));
                scanf("%lf", &this->matrix [i] [j]);
                }
        }
}

void TMatrix::setMatrix(const char fname [LEN], const int n) // ввод из файла библиотекой С
{
    FILE *input;

    input = fopen (fname, "rb");
    if (input == NULL) {
            //printf("Error opening file");
            exit(ERROR_OPEN_FILE);
        }

    double temp = 0;
    this->matrix.resize( n );
    for (int i = 0; i < n; i++)
    {
        this->matrix [ i ].resize ( n );
        for (int j = 0; j < n; j++)
        {
            //fread (&temp, sizeof (double), 1, input); //решение для чтения файла как бинарного
            //fseek(input, sizeof (float), SEEK_CUR); //эксперимент с позициями в файле
            fscanf(input, "%lf", &temp);
            this->matrix [i] [j] = temp;
        }
    }

    if (fclose(input)) printf ("Closing Error");
}

void TMatrix::InitMatrix(const int n) // общая инициализация с меню выбора
{
    char c; //для case
    bool close_code = 0; // если функция возвращает 1 - матрица записана
    char fname[LEN];

    while (getc(stdin) != '\n');

    printf("Выберите метод ввода матрицы\n");
    printf("f - для чтения из файла\n");
    printf("d - для чтения из файла по умолчанию\n");
    printf("h - для ввода вручную (дробный разделитель - запятая)\n");
    printf("q - для окончания инициализации\n");

    do
        {
        c = getc(stdin);
        while (getc(stdin) != '\n'); //очищение stdin от всего, что там осталось
            /*cin >> c;
            while(cin.get() != '\n'); // то же самое, методами С++
            это нужно для корректного считывания имени файла*/
            switch ( c )
            {
                case 'f':
                    printf("Enter input filename no longer then 128 symbols\n");
                    fflush (stdin);
                    gets (fname);
                    setMatrix(fname, n);
                    printf("Initialized\n");
                    close_code = 1;
                    break;
                case 'd':
                    printf("Matrix from file /home/vlad/matrix initialized\n");
                    setMatrix("/home/vlad/matrix", n);
                    close_code = 1;
                    break;
                case 'h':
                    setMatrix(n);
                    printf("Initialized\n");
                    while (getc(stdin) != '\n');
                    close_code = 1;
                    break;
               case 'q':
                    if (!close_code) printf("There is no matrix, try again\n");
                    break;
                default:
                    printf("Wrong key, repeat enter\n");
                    break;
            }
        }
    while ( (c != 'q')||(!close_code) );
}

void TMatrix::getMatrix()
{
    for ( int i = 0; i < this->matrix.size(); i++)
    {
        for ( int j = 0; j < this->matrix.size(); j++)
            printf ("%.3f ", this->matrix [i] [j]);
        printf("\n");
    }
}

void TMatrix::getMatrix(const char *fname)
{
    FILE *output;

    output = fopen (fname, "w");
    if (output == NULL) exit(ERROR_OPEN_FILE);

    for (int i = 0; i < this->matrix.size(); i++)
    {
        for (int j = 0; j < this->matrix.size(); j++) fprintf(output, "%.3f ", this->matrix [i] [j] );
        fprintf(output,"\n");
    }

    if (fclose(output)) printf ("Closing Error");
}

void TMatrix::ShowMatrix()
{
    char c;
    char fname[LEN];

    printf("Выберите метод вывода матрицы\n");
    printf("f - для вывода в файл\n");
    printf("d - для вывода в файл по умолчанию\n");
    printf("s - для вывода на экран\n");
    printf("q - для окончания работы\n");

    do
        {
            c = getc(stdin);
            while (getc(stdin) != '\n'); //очищение stdin от всего, что там осталось
            switch (c)
            {
                case 'f':
                    printf("Enter input filename no longer then 128 symbols\n");
                    fflush (stdin);
                    gets (fname);
                    getMatrix(fname);
                    printf("Записано в файл: "); puts(fname);
                    break;
                case 'd':
                    printf("Записано в файл /home/vlad/outputm\n");
                    getMatrix("/home/vlad/outputm");
                    break;
                case 's':
                    getMatrix();
                    break;
                case 'q':
                    break;
                default:
                    printf("Wrong key, repeat enter\n");
                    break;
            }
        }
    while ( c != 'q' );
}



