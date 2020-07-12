#include "mywidget.h"
#include <QTableWidget>
#include <QHBoxLayout>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <QMessageBox>

void MyWidget::help() //Справка о программе
    {
        QMessageBox::about(this, tr("Про програму"),
                 tr("<center> <b> Ця програма призначена для знаходження оберненої матриці методом Жордана-Гауса та методом Шульца</b> </center> <BR> "
                    "<BR>"
                    " Для початку використання програми Вам необхідно: <BR>"
                    "<BR>""<BR>"
                    "1. Вказати розмірність матриці <BR> ""<BR>"
                    "2. Заповнити таблицю \"Початкова матриця\", де на місці i,j элемента  <BR>"
                    " вказати його значення<BR>"
                    " (Або скористатися кнопкою та сформувати матрицю випадковим чином)<BR>""<BR>"
                    "3. Вибрати спосіб знаходження оберненої матриці<BR>""<BR>"
                    "4. Натиснути на кнопку \"Знайти обернену матрицю\".<BR>""<BR>"
                    "5. Заповниться таблиця \"Обернена матриця\" та отримані дані збережуться в файлі result.txt <BR> "
                    "початкова матриця збережеться в файлі matrix.txt <BR>"));
    }

void MyWidget::setMatrixSize()  //устаналиваем размер таблицы
{

    int n = usr_dim->text().toInt();
    //-----Для исходной матрицы------
    usr_matrix->setColumnCount(n);
    usr_matrix->setRowCount(n);
     usr_matrix -> clearContents();
    //------Для обратной матрицы------
    usr_matrix2->setColumnCount(n);
    usr_matrix2->setRowCount(n);
    usr_matrix2 -> clearContents();
}
void MyWidget::randValue() // Заполняем таблицу случайными элементами
{
    int n = usr_dim->text().toInt();
    int i,j;
    double value;
    for (i=0;i<n;i++)
    {
     for (j=0; j<n; j++)
        {
         value=-300+rand()%500; //генерируем числа в диапазоне от -
         QTableWidgetItem *item1 = new QTableWidgetItem;  //Создаём итем, который положим в таблицу
         item1->setText(QString ("%1").arg(value)); // записываем  текст в итем
         usr_matrix->setItem(i, j, item1); //отправляем в таблицу
        }
    }
}
void MyWidget::crash() // Аварийное завершение программы
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::information(this, tr("Помилка"), tr("Матриця вырождена. Матриця не має обернену."));
}


