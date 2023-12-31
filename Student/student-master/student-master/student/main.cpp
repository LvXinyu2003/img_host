#include "mainwindow.h"
#include <QApplication>
#include<QDebug>
#include<QSqlDatabase>
bool opendatabase();
int main(int argc, char *argv[])
{
    opendatabase();
    QApplication a(argc, argv);

    QFile qssFile("D:\\Qt\\qt_WorkSpace\\Student\\student-master\\student-master\\student\\style.qss");//1.
      if(qssFile.open(QFile::ReadOnly)){//2.
           a.setStyleSheet(qssFile.readAll());//3.
       }
       qssFile.close();//4.
    MainWindow w;

    w.show();

    return a.exec();
}
bool opendatabase()
{
    QSqlDatabase mydb=QSqlDatabase::addDatabase("QSQLITE");

    mydb.setDatabaseName("D:\\Qt\\qt_WorkSpace\\Student\\student-master\\student.db");//release用

    if(mydb.open())
    {
        qDebug()<<"open success";
        return true;
    }
    else
    {
        qDebug()<<"open failed";
        return false;
    }
}
