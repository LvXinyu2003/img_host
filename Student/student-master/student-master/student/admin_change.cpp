#include "admin_change.h"
#include "ui_admin_change.h"
#include<QSqlQueryModel>
#include<QMessageBox>
#include"admin.h"
#pragma execution_character_set("utf-8")//设置中文= =

extern int tt;

admin_change::admin_change(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::admin_change)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/img/123.png"));
     setWindowTitle("添加学生");
}

admin_change::~admin_change()
{
    delete ui;
}

void admin_change::on_pushButton_exit_clicked()
{
    close();
}

void admin_change::on_pushButton_enter_clicked()
{
    QString name,number,Class,sex,age,password;
    name=ui->lineEdit_name->text();
    number=ui->lineEdit_number->text();
    Class=ui->lineEdit_class->text();
    sex=ui->lineEdit_sex->text();
    age=ui->lineEdit_age->text();
    password=ui->lineEdit_passowrd->text();

        QString sql1;
        sql1="select count (*) from Student where Sno='"+number+"'";
        QSqlQueryModel *model1=new QSqlQueryModel;
        model1->setQuery(sql1);
        QModelIndex index1=model1->index(0,0);
        if(index1.data()!=0)
        {
            QMessageBox::about(NULL,"警告","系统中已有这位学生");
        }
        else
        {
            QString sql2;
            QSqlQueryModel *model2=new QSqlQueryModel;
            sql2="insert into Student values ('"+number+"','"+name+"','"+sex+"','"+age+"','"+Class+"','"+password+"')";
            model2->setQuery(sql2);
            admin ad;
            ad.init();
            QMessageBox::about(NULL,"提示","系统信息添加成功");
        }




}
