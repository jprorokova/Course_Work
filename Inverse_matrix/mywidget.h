#ifndef MYWIDGET_H
#define MYWIDGET_H
#include <QTableWidget>
#include <QSpinBox>
#include <QtGui>
#include <qmenu.h>
#include <QCheckBox>
#include<QMenuBar>
#include<QLabel>
#include <QWidget>
#include<QPushButton>
#include<QListWidgetItem>
#include<stdlib.h>
#include <QRadioButton>
#include <QStatusBar>
#include "matrix.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MyWidget;}
QT_END_NAMESPACE
class Matrix;
class MyWidget : public QWidget
{
    Q_OBJECT
    protected:
        QMenuBar *menu;
        QLabel *lbl_dim;
        QLabel *lbl_matrix;
        QLabel *lbl_matrix2;
        QSpinBox *usr_dim;
        QTableWidget *usr_matrix;
        QTableWidget *usr_matrix2;
        QPushButton *btn_rand;
        QPushButton *btn_solve;
        QLineEdit *dsp_maxNev;
        QRadioButton *item_1;
        QRadioButton *item_2;
        QStatusBar *status;
public:
    MyWidget(QWidget *parent = nullptr);
    ~MyWidget();
protected:
    Ui::MyWidget *ui;
    Matrix* m;
    void SaveData1(double **A, int k);
    void SaveData2(double **B, int k);
    void ShowValue(double** A);
    void clearMem(double **A);
    double** tableToArray();
    void badValue ();
public slots:
    void setMatrixSize();
    void randValue();
    void mSolve();
    void crash();
    void help();
   friend class Matrix;
};
#endif // MYWIDGET_H
