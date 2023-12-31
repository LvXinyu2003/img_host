#include "change.h"
#include "ui_change.h"
#include<QSqlQueryModel>
#include<QMessageBox>
#include"admin.h"
extern int tt;
extern int column;
extern QString str1;
extern QString str2;
extern QString stuSno;
extern QString teacher;
change::change(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::change)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/img/123.png"));
     setWindowTitle("修改密码");
}

change::~change()
{
    delete ui;
}

void change::on_pushButton_exit_clicked()
{
    close();
}

void change::on_pushButton_dele_clicked()
{
    QSqlQueryModel *model=new QSqlQueryModel;
    QSqlQueryModel *model2=new QSqlQueryModel;
    QString name,sql,sql1;
    name=ui->lineEdit_name->text();
    if(tt==3)
    {
        if(column==4)
        {
     sql="update SC set Grade='"+name+"'  where Sno='"+str1+"' AND Cno='"+str2+"' ";
       model->setQuery(sql);
        QMessageBox::about(NULL,"提醒","修改成功");
        close();
        }
    }else if(tt==1)
    {
            if(column==1)//姓名
       sql="update Student set Sname='"+name+"'  where Sno='"+str1+"'";
            else if(column==2)//性别
       sql="update Student set Ssex='"+name+"'  where Sno='"+str1+"'";
            else if(column==3)//年龄
       sql="update Student set Sage='"+name+"'  where Sno='"+str1+"'";
            else if(column==4)//专业
       sql="update Student set Sdept='"+name+"'  where Sno='"+str1+"'";
            else if(column==5)//专业
       sql="update Student set password='"+name+"'  where Sno='"+str1+"'";
            model->setQuery(sql);
             QMessageBox::about(NULL,"提醒","修改成功");
             close();


    }else if(tt==2)
    {
            if(column==1)//课程名
       sql="update Course set Cname='"+name+"'  where Cno='"+str1+"'";
            else if(column==2)//先修课
       sql="update Course set Cpno='"+name+"'  where Cno='"+str1+"'";
            else if(column==3)//学分
       sql="update Course set Ccredit='"+name+"'  where Cno='"+str1+"'";


            model->setQuery(sql);
             QMessageBox::about(NULL,"提醒","修改成功");
             close();


    }else if(tt==5)
    {
        sql="update Student set password='"+name+"' where Sno='"+stuSno+"'";
        model->setQuery(sql);
         QMessageBox::about(NULL,"提醒","修改成功");
         close();

    }else if(tt==6)
    {
        sql="update teacher set adpassword='"+name+"' where admin='"+teacher+"'";
        model->setQuery(sql);
         QMessageBox::about(NULL,"提醒","修改成功");
         close();
    }
}


