#ifndef MATRIX_H
#define MATRIX_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <mywidget.h>
QT_BEGIN_NAMESPACE

QT_END_NAMESPACE

class MyWidget;
class Matrix:public QWidget
{

public:
   Matrix();

private:
    static long int iter;
    static long int oper;

    double Determinant(double **mas,int m);
    double** CreateMatrix(int n);
    double** transpose(double** matrix,int n);
    double** multiplication(int n, double** A, double** B);
    double** multiplication(int n, double k, double** B);
    double findCoef(int n,double** matrix);
    double** countPsi(int n,double** I, double** B, double** U0);
    double** SumMatrix(int n, double** A, double** B);
    double** Gauss(int n,double** A);
    double** Shulz(int n,double** A);
    friend class MyWidget;
};

#endif // MATRIX_H

