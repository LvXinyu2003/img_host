#include "grade.h"
#include "ui_grade.h"
#include<QSqlQueryModel>
#include<QMessageBox>
#include"admin.h"
grade::grade(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::grade)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/img/123.png"));
    setWindowTitle("添加成绩");
}

grade::~grade()
{
    delete ui;
}

void grade::on_pushButton_exit_clicked()
{
    close();
}

void grade::on_pushButton_enter_clicked()
{
    QString name,number,grade;
    name=ui->lineEdit_name->text();
    number=ui->lineEdit_number->text();
    grade=ui->lineEdit_grade->text();

    QString sql1;
    sql1="select count (*) from SC where Sno='"+number+"' AND Cno='"+name+"' ";
    QSqlQueryModel *model1=new QSqlQueryModel;
    model1->setQuery(sql1);
    QModelIndex index1=model1->index(0,0);
    if(index1.data()!=0)
    {
       QMessageBox::about(NULL,"警告","系统已有这个成绩");
    }
    else
    {
        QString sql2;
        QSqlQueryModel *model2=new QSqlQueryModel;
        sql2="insert into  SC values ('"+number+"','"+name+"','"+grade+"')";
        model2->setQuery(sql2);
        admin ad;
        ad.init();
        QMessageBox::about(NULL,"提示","成绩添加成功");
    }
}
