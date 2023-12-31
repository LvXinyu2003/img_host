#include "coursedele.h"
#include "ui_coursedele.h"
#include<QMessageBox>
#include<QSqlQueryModel>

coursedele::coursedele(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::coursedele)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/img/123.png"));
     setWindowTitle("删除课程");
}

coursedele::~coursedele()
{
    delete ui;
}

void coursedele::on_pushButton_exit_clicked()
{
    close();
}

void coursedele::on_pushButton_dele_clicked()
{
    QSqlQueryModel *model=new QSqlQueryModel;
    QSqlQueryModel *model2=new QSqlQueryModel;
    QString name,sql,sql2;
    name=ui->lineEdit_name->text();
    sql2="select count (*) from Course where Cno='"+name+"'";
    model2->setQuery(sql2);
    QModelIndex index1=model2->index(0,0);

    if(index1.data()==0)
    {
       QMessageBox::about(NULL,"警告","无此课程");
    }
    else
    {
        sql="delete from Course where Cno='"+name+"'";
        model->setQuery(sql);
        QMessageBox::about(NULL,"提示","删除成功");
    }
}
