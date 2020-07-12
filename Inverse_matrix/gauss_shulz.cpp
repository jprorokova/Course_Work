#include "mywidget.h"

#include <math.h>
#include <float.h>
#include <QTableWidget>
#include <QCheckBox>
#include <iostream>
#include <algorithm>
#include <cmath>
#include<stdlib.h>
#include <QStatusBar>
#include "matrix.h"

class Matrix;
class MyWidget;
long int Matrix::iter = 0;
long int Matrix::oper = 0;
/* Описание метода Гаусса */
void MyWidget::mSolve()
{
    int n = usr_dim->text().toInt();
    double** A=tableToArray();

    if(A!=0x0){

        if(item_1->isChecked()){
            SaveData2(A,n);
            double** B = m->Gauss(n,A);
            if(B==0x0){
                crash();
            }
            else{
                ShowValue(B);//заполняет таблицу полученными данными (на место исходной таблицы вставит верхне-треугольную матрицу
                SaveData1(B,n);
                clearMem(A);//очищает память, выделенную под таблицу
                clearMem(B);
            }
            //else {status->showMessage("Заполните исходную матрицу числами");} //если была введена тесктовая строка, а не число
            QString s = QString::number(m->iter);
            QString y = QString::number(m->oper);
            status->showMessage("Кількість ітерацій: "+s+"  Кількість операцій: "+y);

        }
        else if(item_2->isChecked()){
            SaveData2(A,n);
            double** B = m->Shulz(n,A);
            if(B==0x0){
                crash();
            }
            else{
                ShowValue(B);//заполняет таблицу полученными данными (на место исходной таблицы вставит верхне-треугольную матрицу
               SaveData1(B,n);
                clearMem(A);//очищает память, выделенную под таблицу
                clearMem(B);
            }
            //else {status->showMessage("Заполните исходную матрицу числами");} //если была введена тесктовая строка, а не число
            QString s = QString::number(m->iter);
            QString y = QString::number(m->oper);
            status->showMessage("Кількість ітерацій: "+s+"  Кількість операцій: "+y);


        }
       else{
            status->showMessage("Оберіть метод пошуку оберненої матриці");
        }
    }
    else{
       status->showMessage("Заповніть початкову матрицю числами"); //если была введена тесктовая строка, а не число
    }





}
double** Matrix::Gauss(int n,double** A){

    double** B = CreateMatrix(n);//матрица размером с исходную
    iter = 0;
    oper=0;




     //если получили правильные данные

        if(Determinant(A, n)==0){
            return 0x0;
            //d->crash();
        }
        else{
        float temp;

            //создаем единичную матрицу
            for (int i = 0; i < n; i++) {

                for (int j = 0; j <  n; j++) {
                    iter++;

                    if (j == i )
                       B[i][j] = 1;//заполняем как единичную
                    else{ B[i][j] = 0;}
                }
            }
            //для каждой матрицы А и В
            // Меняем строки матрицы,
                 // смена строк начнется с последнего ряда
            for (int i = n - 1; i > 0; i--) {

                // Обмен всех элементов двух строк
                 if (A[i - 1][0] < A[i][0])
                 for (int j = 0; j < n; j++) {
                        iter++;
                        // Перестановка строки, если выше
                       // условие выполнено.
                 temp = A[i][j];
                 A[i][j] = A[i - 1][j];
                 A[i - 1][j] = temp;

                 temp = B[i][j];
                 B[i][j] = B[i - 1][j];
                 B[i - 1][j] = temp;
                    }

            }




            // из элемента строки вычитаем произведение i,k-го элемента и
                 // константы, кратной другой строке матрицы
            for (int i = 0; i < n; i++) {

                for (int j = 0; j < n; j++) {

                    if (j != i) {

                        temp = A[j][i] / A[i][i];
                      oper++;
                        for (int k = 0; k <  n; k++) {
                        iter++;
                            A[j][k] -= A[i][k] * temp;
                             B[j][k] -= B[i][k] * temp;
                           oper+=4;
                        }
                    }
                }
            }

            // Умножаем каждую строку на ненулевое целое число.
                 // Делим элемент строки на диагональный элемент
            for (int i = 0; i < n; i++) {

                temp = A[i][i];
                for (int j = 0; j <  n; j++) {
                //iter++;
                    A[i][j] = A[i][j] / temp;
                     B[i][j] = B[i][j] / temp;
                     oper+=1;
                }
            }

    }

     return B;

}

//вычисление детерминанта
double Matrix::Determinant(double** mas,int m) {
    int i,j, k, s;
    double d;
    double** p;
     //Матрица без строки и столбца
    p = new double* [m-1];
    for (i = 0; i < m-1; i++)
        p[i] = new double[m-1];
    j = 0; d = 0;
    k = 1; //(-1) в степени i
    s = m - 1;
    if (m < 1) { return 0; }
    if (m == 1) {
        d = mas[0][0];
        return d;
    }
    if (m == 2) {
        d = mas[0][0] * mas[1][1] - (mas[1][0] * mas[0][1]);

        return(d);
    }
    if (m > 2) {
//

                   int l = 1;
                   for(int i = 0; i < m; ++i){

                       int x = 0, y = 0;
                       for(int j = 1; j < m; ++j){
                         for(int k = 0; k < m; ++k){
                           if(i == k) continue;
                          p[x][y] = mas[j][k];
                          ++y;
                          if(y == m - 1){
                              y = 0;
                              ++x;
                          }
                       }
                       }
                       d += l * mas[0][i] * Determinant(p,s);

                       l *= (-1);
                   }
               }
     return(d);


    }



//основная функция метода шульца
double** Matrix::Shulz(int n,double** B){
     oper = 0;
    iter=0;



         if (Determinant(B, n) == 0) {
             return 0x0;

         }
         else{


             //транспонировка матрицы
             double** BT = CreateMatrix(n);
             BT = transpose(B,n);

             //поиск матрицы приближения
             double** U0 = CreateMatrix(n);

             U0 = multiplication(n,(1 / findCoef(n,multiplication(n,B, BT))), BT);

             //точность
             double e = 0.001;
             //матрица для проверки точности на каждой итерации
             double** Psi = CreateMatrix(n);


             //точность матрицы
             double toch = 1;
             //


             //единичная матрица
             double** I = CreateMatrix(n);
             for (int i = 0; i < n; i++) {
                 for (int j = 0; j < n; j++) {
                     I[i][j] = 0;
                     if (i == j) { I[i][j] = 1; }
                 }
             }
             while (toch > e) {

                 Psi = countPsi(n,I,B, U0);


                 toch = findCoef(n,Psi);

                 if (toch <= e) {
                     //
                     break;
                 }
                iter++;
                 U0 = multiplication(n,U0, SumMatrix(n,I, Psi));

             }
             for (int i = 0; i < n; i++) {
                 for (int j = 0; j < n; j++) {
                     B[i][j] = U0[i][j];
                     iter++;
                 }
             }
             transpose(B, n);
             return B;
     }
}
//функции для метода Шульца
double** Matrix::CreateMatrix(int n) {
    double** matrix = new double* [n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new double[n];

    }
    return matrix;
}
double** Matrix::transpose(double** matrix,int n)
{
    double t;
        double** tr = CreateMatrix(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                tr[i][j] = matrix[i][j];
               iter++;
            }
        }
        for (int i = 0; i < n; ++i)
        {
            for (int j = i; j < n; ++j)
            {
                t = tr[i][j];
                tr[i][j] = tr[j][i];
                tr[j][i] = t;
                iter++;
            }
        }
        return tr;
}
double** Matrix::multiplication(int n, double** A, double** B) {
    double** C = CreateMatrix(n);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            C[i][j] = 0;
            for (int k = 0; k < n; ++k){
               iter++;
                C[i][j] += A[i][k] * B[k][j];
                oper+=2;
            }
        }
    }

    return C;
}
double** Matrix::multiplication(int n, double k, double** B) {
    double** C = CreateMatrix(n);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
                C[i][j] = k*B[i][j];
                oper++;
                iter++;
        }
    }

    return C;
}


double Matrix::findCoef(int n,double** matrix) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double b = matrix[i][j] * matrix[i][j];
            sum += b;
            iter++;
            oper++;
        }
    }

    double coef = sqrt(sum);
    return coef;
}
double** Matrix::countPsi(int n,double** I, double** B, double** U0) {
    double** Psi = CreateMatrix(n);
    double** Mult = CreateMatrix(n);
    Mult = multiplication(n, B, U0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            Psi[i][j] = I[i][j] - Mult[i][j];
            oper++;
            iter++;
        }
    }
    return Psi;
}
double** Matrix::SumMatrix(int n, double** A, double** B) {
    double** C = CreateMatrix(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
            oper++;
            iter++;
        }
    }
    return C;
}

