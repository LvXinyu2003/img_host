#include "course.h"
#include "ui_course.h"
#include<QSqlQueryModel>
#include<QMessageBox>
#include"admin.h"


extern int tt;
course::course(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::course)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/img/123.png"));
     setWindowTitle("添加课程");
}

course::~course()
{
    delete ui;
}


void course::on_pushButton_exit_clicked()
{
     close();
}

void course::on_pushButton_enter_clicked()
{
    QString name,number,xianxiu,credit;
    name=ui->lineEdit_name->text();
    number=ui->lineEdit_number->text();
    xianxiu=ui->lineEdit_xianxiu->text();
    credit=ui->lineEdit_credit->text();

    QString sql1;
    sql1="select count (*) from Course where Cno='"+number+"'";
    QSqlQueryModel *model1=new QSqlQueryModel;
    model1->setQuery(sql1);
    QModelIndex index1=model1->index(0,0);
    if(index1.data()!=0)
    {
       QMessageBox::about(NULL,"警告","系统中已有这门课");
    }
    else
    {
        QString sql2;
        QSqlQueryModel *model2=new QSqlQueryModel;
        sql2="insert into Course values ('"+number+"','"+name+"','"+xianxiu+"','"+credit+"')";
        model2->setQuery(sql2);
        admin ad;
        ad.init();
        QMessageBox::about(NULL,"提示","系统信息添加成功");
    }
}
