#include "mywidget.h"
#include <QMainWindow>
#include <QTableWidget>
#include <QHBoxLayout>
#include <iomanip>
#include <stdlib.h>
#include <qtextcodec.h>
#include <QMenuBar>
#include "ui_mywidget.h"
#include <QLineEdit>
#include <QListWidget>
 #include <QRadioButton>
#include <QGroupBox>
#include <QStatusBar>
#include "matrix.h"
class Matrix;
MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    QMainWindow *MainForm = new QMainWindow;
    QWidget *window = new QWidget;//создаём виджет
    status = new QStatusBar;
    menu = new QMenuBar;
    MainForm->setMenuBar(menu);

    QAction *newHelp = new QAction(tr("Довідка"), this);
    connect(newHelp, SIGNAL(triggered()), this, SLOT( help() ) );
    MainForm->menuBar()->addAction(newHelp);



    /* Создаем надписи */
    lbl_dim = new QLabel(tr("Розмірність"));  //создаём надписи
    lbl_matrix = new QLabel(tr("Початкова матриця:"));
    lbl_matrix2 = new QLabel(tr("Обернена матриця:"));
    /* Создаем список методов для выбора */



         item_1 = new QRadioButton("метод Жордана-Гауса ");
         item_1->setCheckable(true);

         item_2 = new QRadioButton("метод Шульца ");
         item_2->setCheckable(true);


//   }
    /* Создаем поля, которе пользователь сможет редактировать */
    usr_dim = new QSpinBox(this);            //создаём бокс для чисел
    usr_matrix = new QTableWidget(2,2);      //создаём таблицу
    usr_matrix2 = new QTableWidget(2,2);      //создаём таблицу

    usr_dim->setValue(2);
    usr_dim->setMinimum(2); //ограничиваем минимальное значение для размерности
    usr_dim->setMaximum(10);
    usr_dim->setMaximumWidth(1000000);

    /* Создаем кнопки */
    btn_rand = new QPushButton(tr("Заповнити матрицю випадковими числами")); //создаём кнопки
    btn_solve = new QPushButton(tr("Знайти обернену матрицю"));
    dsp_maxNev = new QLineEdit(this);
    dsp_maxNev->setEnabled(0);
    dsp_maxNev->setMaximumWidth(1000000);

    /* Устаналиваем связь между сигналами элементов и слотами, которые будут их обрабатывать */
    QObject::connect (usr_dim, SIGNAL (valueChanged(int)), this, SLOT(setMatrixSize()));


    QObject::connect (btn_rand, SIGNAL (clicked()), this, SLOT(randValue()));
    QObject::connect (btn_solve, SIGNAL (clicked()), this, SLOT(mSolve()));

    /* Создаём лейауты. в которые кладём наши элементы и группируем */
    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout -> addWidget(lbl_dim);//добавляем строку размерность
    topLayout -> addWidget(usr_dim);//добавляем бокс для чисел
    topLayout -> addStretch();//добавляем место для изменения размерности от 2 до 100
    QVBoxLayout *vbox = new QVBoxLayout;//бокс для выбора метода
        vbox->addWidget(item_1);
        vbox->addWidget(item_2);
        vbox->addStretch(1);
    QVBoxLayout *middleLayout = new QVBoxLayout;//

    middleLayout -> addWidget(lbl_matrix);//
    middleLayout -> addWidget(usr_matrix);//добавляем таблицу
    QVBoxLayout *middle2Layout = new QVBoxLayout;//
    middle2Layout -> addWidget(lbl_matrix2);//
    middle2Layout -> addWidget(usr_matrix2);//добавляем таблицу
    QHBoxLayout *middle3Layout = new QHBoxLayout;
    middle3Layout -> addWidget(btn_rand);
    middle3Layout -> addWidget(btn_solve);
    QVBoxLayout *mainLayout = new QVBoxLayout;

    //mainLayout->addLayout (Menu);
    mainLayout->addLayout (topLayout);
    mainLayout->addLayout (vbox);
    mainLayout->addLayout (middleLayout);
    //mainLayout->addWidget(listWidget);//добавляем список методов в основной лэйаут
    mainLayout->addLayout (middle2Layout);
    mainLayout->addLayout (middle3Layout);
    mainLayout->addWidget(status);

    window ->setLayout(mainLayout);
    MainForm->setCentralWidget(window);
    MainForm->setMinimumHeight(700);
    MainForm->setMinimumWidth(800);
    MainForm->show();


}

MyWidget::~MyWidget()
{
    delete ui;
}
