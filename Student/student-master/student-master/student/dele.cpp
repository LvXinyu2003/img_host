#include "dele.h"
#include "ui_dele.h"
#include<QMessageBox>
#include<QSqlQueryModel>
#pragma execution_character_set("utf-8")//设置中文= =
dele::dele(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::dele)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/img/123.png"));
     setWindowTitle("删除学生");
}

dele::~dele()
{
    delete ui;
}

void dele::on_pushButton_exit_clicked()
{
    close();
}

void dele::on_pushButton_dele_clicked()
{
    QSqlQueryModel *model=new QSqlQueryModel;
    QSqlQueryModel *model2=new QSqlQueryModel;
    QString name,sql,sql2;
    name=ui->lineEdit_name->text();
    sql2="select count (*) from Student where Sno='"+name+"'";
    model2->setQuery(sql2);
    QModelIndex index1=model2->index(0,0);

    if(index1.data()==0)
    {
        QMessageBox::about(NULL,"警告","系统中并无此人");
    }
    else
    {
        sql="delete from Student where Sno='"+name+"'";
        model->setQuery(sql);
        QMessageBox::about(NULL,"提示","删除成功");
    }
}
