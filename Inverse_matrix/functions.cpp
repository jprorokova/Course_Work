#include "mywidget.h"
#include <QTableWidget>
#include <iomanip>
#include <stdlib.h>
#include <qtextcodec.h>
#include <float.h>
#include <QBrush>
#include <QMessageBox>
#include <QFileDialog>
#include <fstream>
#include <QString>
#include "matrix.h"
/* Заполняем таблицу итоговыми результатами */
void MyWidget::ShowValue(double** A)
{
    int n = usr_dim->text().toInt();
    int i,j;
    double value;
    for (i=0;i<n;i++)
     for (j=0; j<n; j++)
        {
         value=A[i][j]; //Берем i,j элемент
         QTableWidgetItem *item = new QTableWidgetItem;  //Создаём итем, который положим в таблицу
         item->setText(QString ("%1").setNum(value)); // записываем  текст в итем
         usr_matrix2->setItem(i, j, item); //отправляем в таблицу
        }
}
void MyWidget::SaveData1(double **A, int k){
    QString filename = "result.txt";
      QFile file(filename);
      // Открываем файл в режиме "Только для записи"
       if (file.open(QIODevice::WriteOnly)) {
         QTextStream out(&file); // поток записываемых данных направляем в файл
         for(int i = 0;i<k;i++){
             for(int j = 0;j<k;j++){
                 out << A[i][j] << "  ";
             }
             out<< "\r\n"<<endl;

         }
       }
}
void MyWidget::SaveData2(double **B, int k){
       QString name = "matrix.txt";
       QFile file2(name);
         // Открываем файл в режиме "Только для записи"
          if (file2.open(QIODevice::WriteOnly)) {
            QTextStream out(&file2); // поток записываемых данных направляем в файл
            for(int i = 0;i<k;i++){
                for(int j = 0;j<k;j++){
                    out << B[i][j] << "  ";
                }
                out<< "\r\n"<<endl;

            }
          }

}
/* Переносим данные из таблицы в матрицу для вычислений */
double** MyWidget::tableToArray()
{
    int n = usr_dim -> text().toInt();
    int i,j;
    bool isOK = false;
    double** A = new double* [n]; //Создаем массив под заданную матрицу
    for (i = 0; i < n ; i++)
         A[i]=new double [n];
    /* Заполнение матрицы исходными данными */
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if(usr_matrix->item(i,j)==0){
                isOK=false;

            }
            else{
            A[i][j]=usr_matrix->item(i,j)->text().toDouble(&isOK);

            }
            if (isOK == false)
            {
                badValue();
                return 0x0;
            }
        }
    }
    return A;
}
/*Выводим сообщение о неверном типе введенных данных */
void MyWidget::badValue()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::warning(this, tr("Помилка"), tr(" Переконайтеся, що Ви заповнили початкову матрицю числами."));
}


/* Очищаем память по завершению работы программы */
void MyWidget::clearMem(double** A)
{
    int n = usr_dim->text().toInt();
    for(int i = 0; i < n; i++)
       delete[] A[i];
    delete A;
}


    


