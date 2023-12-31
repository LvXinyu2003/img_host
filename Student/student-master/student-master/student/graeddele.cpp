#include "graeddele.h"
#include "ui_graeddele.h"
#include<QMessageBox>
#include<QSqlQueryModel>

graeddele::graeddele(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::graeddele)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/img/123.png"));
    setWindowTitle("删除成绩");
}

graeddele::~graeddele()
{
    delete ui;
}

void graeddele::on_pushButton_exit_clicked()
{
    close();
}

void graeddele::on_pushButton_dele_clicked()
{
    QSqlQueryModel *model=new QSqlQueryModel;
    QSqlQueryModel *model2=new QSqlQueryModel;
    QString sno,cno,sql2,sql;
    sno=ui->lineEdit_sno->text();
     cno=ui->lineEdit_cno->text();
    sql2="select count (*) from SC where Sno='"+sno+"' AND Cno='"+cno+"'";
    model2->setQuery(sql2);
    QModelIndex index1=model2->index(0,0);

    if(index1.data()==0)
    {
        QMessageBox::about(NULL,"警告","系统没有这门成绩");
    }
    else
    {
        sql="delete from SC where Sno='"+sno+"' AND Cno='"+cno+"'";
        model->setQuery(sql);
        QMessageBox::about(NULL,"提示","删除成功");
    }
}
