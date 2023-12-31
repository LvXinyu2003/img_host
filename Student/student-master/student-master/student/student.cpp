#include "student.h"
#include "ui_student.h"
#include "change.h"
#include "admin.h"
#include<QDebug>
#include<QSqlQueryModel>
#pragma execution_character_set("utf-8")//设置中文= =
extern int tt;
QString stuSno;
student::student(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::student)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/img/123.png"));


}

student::~student()
{
    delete ui;
}

void student::on_pushButton_clicked()
{
    close();
}
void student::init()
{
    qDebug()<<stuName;
    stuSno=stuName;
    QString sql_stu,sql,sql1,sql2;
    sql="select Sno,Sname from Student where Sno='"+stuName+"'";
    sql1="select avg(Grade) from SC where Sno='"+stuName+"'";
    sql2="select sum(Ccredit) from SC,Course where Sno='"+stuName+"' AND SC.Cno=Course.Cno";
    sql_stu="select Student.Sno as 学号,Sname as 姓名,Ssex as 性别,Sage as 年龄,Sdept as 专业,SC.Cno as 课程号,Cname as 课程名,Grade as 成绩,Ccredit as 学分,Cpno as 先修课,password as 密码 from Student,SC,Course where Student.Sno=SC.Sno AND SC.Cno=Course.Cno AND Student.Sno='"+stuName+"'";
    QSqlQueryModel *modelx=new QSqlQueryModel;
    modelx->setQuery(sql_stu);
    QSqlQueryModel *model=new QSqlQueryModel;
    model->setQuery(sql);
    QSqlQueryModel *model1=new QSqlQueryModel;
    model1->setQuery(sql1);
    QSqlQueryModel *model2=new QSqlQueryModel;
    model2->setQuery(sql2);
    ui->tableView_3->horizontalHeader()->setVisible(false);
    ui->tableView_3->verticalHeader()->setVisible(false);
    ui->tableView_2->horizontalHeader()->setVisible(false);
    ui->tableView_2->verticalHeader()->setVisible(false);
    ui->tableView_4->horizontalHeader()->setVisible(false);
    ui->tableView_4->verticalHeader()->setVisible(false);
    ui->tableView->setModel(modelx);
    ui->tableView_2->setModel(model);
    ui->tableView_3->setModel(model1);
       ui->tableView_4->setModel(model2);
}

void student::on_pushButton_2_clicked()
{
    tt=5;
    chang=new change;
    chang->show();


}
