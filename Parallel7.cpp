#include <iostream>
#include <omp.h>
#include <cstdlib>

using namespace std;



void randomMatrix(int** matrix, int n, int m, int val=1)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            matrix[i][j] = val;
}

void printMatrix(int** matrix, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            cout << "" << matrix[i][j] << " ";
        cout << endl;
    }
}

int main()
{
    int n1, m1, n2, m2;
    cout << "Matrix 1:\nEnter n: ";
    cin >> n1;
    cout << "Enter m: ";
    cin >> m1;
    cout << "Matrix 2:\nEnter n: ";
    cin >> n2;
    cout << "Enter m: ";
    cin >> m2;
    //n1 = 1000;
    //n2 = 500;
    //m1 = 500;
    //m2 = 2000;

    if (n2 != m1)
        cout << "Произведение матриц выполнить невозможно: кол-во столбцов в 1 матрице не равно кол-ву строк во 2";
    else
    {
        int** matrix1, ** matrix2;

        matrix1 = new int* [n1];
        matrix2 = new int* [n2];

        for (int i = 0; i < n1; i++)
            matrix1[i] = new int[m1];
        for (int j = 0; j < n2; j++)
            matrix2[j] = new int[m2];

        randomMatrix(matrix1, n1, m1);
        randomMatrix(matrix2, n2, m2);

        if (n1 <= 10 && m1 <= 10 && n2 <= 10 && m2 <= 10)
        {
            cout << "Matrix 1: " << endl;
            printMatrix(matrix1, n1, m1);
            cout << "Matrix 2: " << endl;
            printMatrix(matrix2, n2, m2);
        }
   

        int** result;
        result = new int* [n1];
        for (int k = 0; k < n1; k++)
            result[k] = new int[m2];
        randomMatrix(result, n1, m2, 0);

        int threadsNum;
        cout << "Enter threads: ";
        cin >> threadsNum;

        double start, end;

        omp_set_num_threads(threadsNum);
        int i, j, k;
        start = omp_get_wtime();
#pragma omp parallel default(none) shared(matrix1, matrix2, result) private(j, k, i)
        {
#pragma omp for schedule(static)
            for (j = 0; j < m2; j++) {
                for (k = 0; k < m1; k++)
                    for (i = 0; i < n1; i++)
                        result[i][j] += (matrix1[i][k] * matrix2[k][j]);
            }
        }
        end = omp_get_wtime();

        if (n1 <= 10 && m2 <= 10)
        {
            cout << "Result j-k-i: " << endl;
            printMatrix(result, n1, m2);
        }

        cout << "Time: " << end - start << endl;

        randomMatrix(result, n1, m2, 0);

        omp_set_num_threads(threadsNum);
        start = omp_get_wtime();
#pragma omp parallel default(none) shared(matrix1, matrix2, result) private(k, i, j)
        {
#pragma omp for schedule(static)
            for (k = 0; k < m1; k++) {
                for (i = 0; i < n1; i++)
                    for (j = 0; j < m2; j++)
                        result[i][j] += (matrix1[i][k] * matrix2[k][j]);
            }
        }
        end = omp_get_wtime();

        if (n1 <= 10 && m2 <= 10)
        {
            cout << "Result j-k-i: " << endl;
            printMatrix(result, n1, m2);
        }

        cout << "Time: " << end - start;
    }
    
}

