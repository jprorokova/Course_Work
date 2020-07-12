#include <QApplication>
#include<QTextCodec>
#include "mywidget.h"
int main (int argc, char *argv[])
{
    QTextCodec* codec = QTextCodec::codecForName("UTF-8");

       QTextCodec::setCodecForLocale(codec);
        QApplication qapp(argc, argv);
        qapp.setApplicationName("Inverse Matrix");
        MyWidget myw;
        qapp.exec();
        return 0;
}
