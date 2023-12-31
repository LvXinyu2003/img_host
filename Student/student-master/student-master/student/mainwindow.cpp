#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QSqlQueryModel>
#include<QDebug>
#include<QMessageBox>

QString teacher;

#pragma execution_character_set("utf-8")//设置中文= =
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    stu=new student;
     this->setWindowIcon(QIcon(":/img/123.png"));
     setWindowTitle("登录页");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_exit_clicked()
{
    close();
}

void MainWindow::on_pushButton_regist_clicked()
{
    QString sql1,sql2;
    QString sql3;

    inputName=ui->lineEdit_name->text();
    QString inputPassword=ui->lineEdit_password->text();
    QSqlQueryModel *model1=new QSqlQueryModel;
    QSqlQueryModel *model2=new QSqlQueryModel;
    sql1="select count (*) from teacher where admin='"+inputName+"'";
    model1->setQuery(sql1);
    QModelIndex index1=model1->index(0,0);

    if(index1.data()==0)
    {
        QMessageBox::about(NULL,"提示","用户注册成功");

        sql3="insert into teacher values('"+inputName+"','"+inputPassword+"')";
        QSqlQueryModel *model=new QSqlQueryModel;
        model->setQuery(sql3);
    }
    else if(index1.data()!=0)
    {
        QMessageBox::about(NULL,"提示","用户已经存在");
    }
}

void MainWindow::on_pushButton_login_clicked()
{
    QString sql1,sql2;
    QString sql3;

    QString inputName=ui->lineEdit_name->text();
    QString inputPassword=ui->lineEdit_password->text();

    teacher=inputName;
    QSqlQueryModel *model1=new QSqlQueryModel;
    QSqlQueryModel *model2=new QSqlQueryModel;

    if(0)
    {
        sql1="select count (*) from teacher where admin='"+inputName+"'";
        model1->setQuery(sql1);
        QModelIndex index1=model1->index(0,0);
        sql2="select adpassword from teacher where admin ='"+inputName+"'";
        model2->setQuery(sql2);
        QModelIndex index2=model2->index(0,0);


        if(index1.data()!=0&&inputPassword==index2.data())
        {
            this->setWindowIcon(QIcon(":/img/123.png"));

            QMessageBox::about(NULL,"提示","管理员登陆成功");

            adm=new admin;
            adm->show();

        }
        else
        {
            QMessageBox::about(NULL,"提示","用户名或密码错误");
        }
    }
    else
    {
        sql1="select count (*) from Student where Sno='"+inputName+"'";
        model1->setQuery(sql1);
        QModelIndex index1=model1->index(0,0);
        sql2="select password from Student where Sno ='"+inputName+"'";
        model2->setQuery(sql2);
        QModelIndex index2=model2->index(0,0);

        if(index1.data()!=0&&inputPassword==index2.data())
        {
            QMessageBox::about(NULL,"提示","用户登录成功");
            //sql3="insert into student(name,password) values('"+inputName+"','"+inputPassword+"')";
            //QSqlQueryModel *model=new QSqlQueryModel;
            //model->setQuery(sql3);

            stu->stuName=inputName;//将登陆的学生信息读取出来
            stu->show();
            stu->init();
            //!!!!!!特别注意
            //! 构造函数会将类成员赋初值，所以必须在这里进行赋值和各种操作，而在student类中再去读取这个窗口的数据，是很难实现的
        }
        else
        {
            QMessageBox::about(NULL,"提示","用户名或密码错误");

        }
    }
}


