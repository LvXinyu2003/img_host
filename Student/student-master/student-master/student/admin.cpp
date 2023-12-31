#include "admin.h"
#include "ui_admin.h"
#include<QSqlQueryModel>
#include<QMessageBox>
#pragma execution_character_set("utf-8")//设置中文= =
int tt=0;
int kk=0;
int row ;
int column;
QString str1;
QString str2,str3,str4,str5;

extern QString teacher;

admin::admin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::admin)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/img/123.png"));


    init();
    connect(ui->lineEdit_findname,SIGNAL(textChanged(QString)),this,SLOT(find()));//将字符变化的事件，与某函数连接
}

admin::~admin()
{
    delete ui;
}
void admin::init()//
{
    QSqlQueryModel *model=new QSqlQueryModel;
      QSqlQueryModel *model1=new QSqlQueryModel;
    QString sql,sql1;
    sql="select Sno as 学号,Sname as 姓名 ,Ssex as 性别,Sage as 年龄,Sdept as 专业,password as 密码  from Student";
   sql1="select admin from teacher where admin='"+teacher+"'";
    model->setQuery(sql);
 model1->setQuery(sql1);

    ui->tableView->setModel(model);
    ui->tableView_2->horizontalHeader()->setVisible(false);
    ui->tableView_2->verticalHeader()->setVisible(false);
    ui->tableView_2->setModel(model1);
}

void admin::on_pushButton_exit_clicked()
{
    close();
}

void admin::on_pushButton_show_clicked()//学生信息显示
{
    tt=1;
    QSqlQueryModel *model=new QSqlQueryModel;
    QString sql;
    sql="select Sno as 学号,Sname as 姓名 ,Ssex as 性别,Sage as 年龄,Sdept as 专业,password as 密码  from Student";
    model->setQuery(sql);

    ui->tableView->setModel(model);
}
void admin::on_pushButton_show_2_clicked()//课程信息显示
{

tt=2;
       QSqlQueryModel *model=new QSqlQueryModel;
       QString sql;
        sql="select Cno as 课程号,Cname as 课程名 ,Cpno as 先修课,Ccredit as 学分 from Course";
        model->setQuery(sql);
      ui->tableView->setModel(model);

}
void admin::on_pushButton_show_3_clicked()  //成绩
{
    tt=3;
    QSqlQueryModel *model=new QSqlQueryModel;
    QString sql;
    sql="select SC.Sno as 学号,Sname as 姓名,SC.Cno as 课程号 ,Cname as 课程名,Grade as 成绩 from SC,Student,Course where SC.Sno=Student.Sno AND SC.Cno=Course.Cno";
    model->setQuery(sql);
    ui->tableView->setModel(model);
}


void admin::on_pushButton_change_clicked()
{
    if(tt==1)
    {
    adminc=new admin_change;
    adminc->show();
    }else if(tt==2)
    {
            cour=new course;
            cour->show();

    }else if(tt==3)
       { grad=new grade;
    grad->show();
    }
}



void admin::on_pushButton_del_clicked()
{
    if(tt==1){
    del=new dele;
    del->show();
    }else if(tt==2)
    {
        courdele=new coursedele;
        courdele->show();

    }else if(tt==3)
    { gradele=new graeddele;
      gradele->show();
 }
}
void admin::find()//需要connect函数进行连接，每当输入框文本发生变化，就执行一边这个函数，而不需要手动点击什么按钮了
{
    QSqlQueryModel *modell=new QSqlQueryModel;
    QString find,sql0;
    find=ui->lineEdit_findname->text();
    if(tt==1){
    if(ui->comboBox_2->currentText()=="姓名搜索")
    sql0="select Sno as 学号,Sname as 姓名 ,Ssex as 性别,Sage as 年龄,Sdept as 专业,password as 密码  from Student where Sname LIKE '%"+find+"%'";
    else if(ui->comboBox_2->currentText()=="学号搜索")
    sql0="select Sno as 学号,Sname as 姓名 ,Ssex as 性别,Sage as 年龄,Sdept as 专业,password as 密码  from Student where Sno LIKE '%"+find+"%'";
else
        sql0="select Sno as 学号,Sname as 姓名 ,Ssex as 性别,Sage as 年龄,Sdept as 专业,password as 密码  from Student";
    modell->setQuery(sql0);
    ui->tableView->setModel(modell);
}
    if(tt==2){
    if(ui->comboBox_2->currentText()=="课程搜索")
    sql0="select Cno as 课程号,Cname as 课程名 ,Cpno as 先修课,Ccredit as 学分 from Course where Cname LIKE '%"+find+"%'";
    else
         sql0="select Cno as 课程号,Cname as 课程名 ,Cpno as 先修课,Ccredit as 学分 from Course";
    modell->setQuery(sql0);
    ui->tableView->setModel(modell);
}
    if(tt==3){
    if(ui->comboBox_2->currentText()=="姓名搜索")
    sql0="select SC.Sno as 学号,Sname as 姓名,SC.Cno as 课程号 ,Cname as 课程名,Grade as 成绩 from SC,Student,Course where SC.Sno=Student.Sno AND SC.Cno=Course.Cno AND Sname LIKE '%"+find+"%'";
else if(ui->comboBox_2->currentText()=="学号搜索")
          sql0="select SC.Sno as 学号,Sname as 姓名,SC.Cno as 课程号 ,Cname as 课程名,Grade as 成绩 from SC,Student,Course where SC.Sno=Student.Sno AND SC.Cno=Course.Cno AND SC.Sno LIKE '%"+find+"%'";
    else if(ui->comboBox_2->currentText()=="课程搜索")
      sql0="select SC.Sno as 学号,Sname as 姓名,SC.Cno as 课程号 ,Cname as 课程名,Grade as 成绩 from SC,Student,Course where SC.Sno=Student.Sno AND SC.Cno=Course.Cno AND Cname LIKE '%"+find+"%'";
    modell->setQuery(sql0);
    ui->tableView->setModel(modell);
}
}

void admin::on_pushButton_order_clicked()//根据combobox显示的文字执行不同的语句
{
    QSqlQueryModel *modell=new QSqlQueryModel;
    QString find,sql0;
    find=ui->lineEdit_findname->text();
    if(ui->checkBox_desc->isChecked())
    {
        if(tt==1)
        if(ui->comboBox->currentText()=="学号")
        {
            sql0="select Sno as 学号,Sname as 姓名 ,Ssex as 性别,Sage as 年龄,Sdept as 专业,password as 密码  from Student order by Sno desc";
        }
        else if(ui->comboBox->currentText()=="年龄")
        {
            sql0="select Sno as 学号,Sname as 姓名 ,Ssex as 性别,Sage as 年龄,Sdept as 专业,password as 密码  from Student order by Sage desc";
        }

        if(tt==2)
        if(ui->comboBox->currentText()=="学分")
           sql0="select Cno as 课程号,Cname as 课程名 ,Cpno as 先修课,Ccredit as 学分 from Course order by Ccredit desc";
        else
                     sql0="select Cno as 课程号,Cname as 课程名 ,Cpno as 先修课,Ccredit as 学分 from Course";


        if(tt==3)
            if(ui->comboBox->currentText()=="学号")
            {

                if(ui->comboBox_2->currentText()=="姓名搜索")
                sql0="select SC.Sno as 学号,Sname as 姓名,SC.Cno as 课程号 ,Cname as 课程名,Grade as 成绩 from SC,Student,Course where SC.Sno=Student.Sno AND SC.Cno=Course.Cno AND Sname LIKE '%"+find+"%'order by SC.Sno desc";
            else if(ui->comboBox_2->currentText()=="学号搜索")
                      sql0="select SC.Sno as 学号,Sname as 姓名,SC.Cno as 课程号 ,Cname as 课程名,Grade as 成绩 from SC,Student,Course where SC.Sno=Student.Sno AND SC.Cno=Course.Cno AND SC.Sno LIKE '%"+find+"%'order by SC.Sno desc";
                else if(ui->comboBox_2->currentText()=="课程搜索")
                  sql0="select SC.Sno as 学号,Sname as 姓名,SC.Cno as 课程号 ,Cname as 课程名,Grade as 成绩 from SC,Student,Course where SC.Sno=Student.Sno AND SC.Cno=Course.Cno AND Cname LIKE '%"+find+"%'order by SC.Sno desc";



            //    sql0="select SC.Sno as 学号,Sname as 姓名,SC.Cno as 课程号 ,Cname as 课程名,Grade as 成绩 from SC,Student,Course where SC.Sno=Student.Sno AND SC.Cno=Course.Cno order by SC.Sno desc";
            }
            else if(ui->comboBox->currentText()=="成绩")
            {
                if(ui->comboBox_2->currentText()=="姓名搜索")
                sql0="select SC.Sno as 学号,Sname as 姓名,SC.Cno as 课程号 ,Cname as 课程名,Grade as 成绩 from SC,Student,Course where SC.Sno=Student.Sno AND SC.Cno=Course.Cno AND Sname LIKE '%"+find+"%'order by Grade desc";
            else if(ui->comboBox_2->currentText()=="学号搜索")
                      sql0="select SC.Sno as 学号,Sname as 姓名,SC.Cno as 课程号 ,Cname as 课程名,Grade as 成绩 from SC,Student,Course where SC.Sno=Student.Sno AND SC.Cno=Course.Cno AND SC.Sno LIKE '%"+find+"%'order by Grade desc";
                else if(ui->comboBox_2->currentText()=="课程搜索")
                  sql0="select SC.Sno as 学号,Sname as 姓名,SC.Cno as 课程号 ,Cname as 课程名,Grade as 成绩 from SC,Student,Course where SC.Sno=Student.Sno AND SC.Cno=Course.Cno AND Cname LIKE '%"+find+"%'order by Grade desc";



            // sql0="select SC.Sno as 学号,Sname as 姓名,SC.Cno as 课程号 ,Cname as 课程名,Grade as 成绩 from SC,Student,Course where SC.Sno=Student.Sno AND SC.Cno=Course.Cno order by Sage desc";
            } else if(ui->comboBox->currentText()=="课程号")
            {
                if(ui->comboBox_2->currentText()=="姓名搜索")
                sql0="select SC.Sno as 学号,Sname as 姓名,SC.Cno as 课程号 ,Cname as 课程名,Grade as 成绩 from SC,Student,Course where SC.Sno=Student.Sno AND SC.Cno=Course.Cno AND Sname LIKE '%"+find+"%'order by SC.Cno desc";
            else if(ui->comboBox_2->currentText()=="学号搜索")
                      sql0="select SC.Sno as 学号,Sname as 姓名,SC.Cno as 课程号 ,Cname as 课程名,Grade as 成绩 from SC,Student,Course where SC.Sno=Student.Sno AND SC.Cno=Course.Cno AND SC.Sno LIKE '%"+find+"%'order by SC.Cno desc";
                else if(ui->comboBox_2->currentText()=="课程搜索")
                  sql0="select SC.Sno as 学号,Sname as 姓名,SC.Cno as 课程号 ,Cname as 课程名,Grade as 成绩 from SC,Student,Course where SC.Sno=Student.Sno AND SC.Cno=Course.Cno AND Cname LIKE '%"+find+"%'order by SC.Cno desc";



            // sql0="select SC.Sno as 学号,Sname as 姓名,SC.Cno as 课程号 ,Cname as 课程名,Grade as 成绩 from SC,Student,Course where SC.Sno=Student.Sno AND SC.Cno=Course.Cno order by Sage desc";
            }


    }
    else
    {
        if(tt==1)
        if(ui->comboBox->currentText()=="学号")
        {
            sql0="select Sno as 学号,Sname as 姓名 ,Ssex as 性别,Sage as 年龄,Sdept as 专业,password as 密码  from Student order by Sno ";
        }
        else if(ui->comboBox->currentText()=="年龄")
        {
            sql0="select Sno as 学号,Sname as 姓名 ,Ssex as 性别,Sage as 年龄,Sdept as 专业,password as 密码  from Student order by Sage ";
        }
        if(tt==2)
        if(ui->comboBox->currentText()=="学分")
           sql0="select Cno as 课程号,Cname as 课程名 ,Cpno as 先修课,Ccredit as 学分 from Course order by Ccredit";
else
             sql0="select Cno as 课程号,Cname as 课程名 ,Cpno as 先修课,Ccredit as 学分 from Course";


        if(tt==3)
            if(ui->comboBox->currentText()=="学号")
            {
                if(ui->comboBox_2->currentText()=="姓名搜索")
                sql0="select SC.Sno as 学号,Sname as 姓名,SC.Cno as 课程号 ,Cname as 课程名,Grade as 成绩 from SC,Student,Course where SC.Sno=Student.Sno AND SC.Cno=Course.Cno AND Sname LIKE '%"+find+"%'order by SC.Sno";
            else if(ui->comboBox_2->currentText()=="学号搜索")
                      sql0="select SC.Sno as 学号,Sname as 姓名,SC.Cno as 课程号 ,Cname as 课程名,Grade as 成绩 from SC,Student,Course where SC.Sno=Student.Sno AND SC.Cno=Course.Cno AND SC.Sno LIKE '%"+find+"%'order by SC.Sno";
                else if(ui->comboBox_2->currentText()=="课程搜索")
                  sql0="select SC.Sno as 学号,Sname as 姓名,SC.Cno as 课程号 ,Cname as 课程名,Grade as 成绩 from SC,Student,Course where SC.Sno=Student.Sno AND SC.Cno=Course.Cno AND Cname LIKE '%"+find+"%'order by SC.Sno";

                //sql0="select SC.Sno as 学号,Sname as 姓名,SC.Cno as 课程号 ,Cname as 课程名,Grade as 成绩 from SC,Student,Course where SC.Sno=Student.Sno AND SC.Cno=Course.Cno order by SC.Sno";
            }
            else if(ui->comboBox->currentText()=="成绩")
            {
                if(ui->comboBox_2->currentText()=="姓名搜索")
                sql0="select SC.Sno as 学号,Sname as 姓名,SC.Cno as 课程号 ,Cname as 课程名,Grade as 成绩 from SC,Student,Course where SC.Sno=Student.Sno AND SC.Cno=Course.Cno AND Sname LIKE '%"+find+"%'order by Grade";
            else if(ui->comboBox_2->currentText()=="学号搜索")
                      sql0="select SC.Sno as 学号,Sname as 姓名,SC.Cno as 课程号 ,Cname as 课程名,Grade as 成绩 from SC,Student,Course where SC.Sno=Student.Sno AND SC.Cno=Course.Cno AND SC.Sno LIKE '%"+find+"%'order by Grade";
                else if(ui->comboBox_2->currentText()=="课程搜索")
                  sql0="select SC.Sno as 学号,Sname as 姓名,SC.Cno as 课程号 ,Cname as 课程名,Grade as 成绩 from SC,Student,Course where SC.Sno=Student.Sno AND SC.Cno=Course.Cno AND Cname LIKE '%"+find+"%'order by Grade";




             //sql0="select SC.Sno as 学号,Sname as 姓名,SC.Cno as 课程号 ,Cname as 课程名,Grade as 成绩 from SC,Student,Course where SC.Sno=Student.Sno AND SC.Cno=Course.Cno order by Grade";
            } else if(ui->comboBox->currentText()=="课程号")
            {
                if(ui->comboBox_2->currentText()=="姓名搜索")
                sql0="select SC.Sno as 学号,Sname as 姓名,SC.Cno as 课程号 ,Cname as 课程名,Grade as 成绩 from SC,Student,Course where SC.Sno=Student.Sno AND SC.Cno=Course.Cno AND Sname LIKE '%"+find+"%'order by SC.Cno";
            else if(ui->comboBox_2->currentText()=="学号搜索")
                      sql0="select SC.Sno as 学号,Sname as 姓名,SC.Cno as 课程号 ,Cname as 课程名,Grade as 成绩 from SC,Student,Course where SC.Sno=Student.Sno AND SC.Cno=Course.Cno AND SC.Sno LIKE '%"+find+"%'order by SC.Cno";
                else if(ui->comboBox_2->currentText()=="课程搜索")
                  sql0="select SC.Sno as 学号,Sname as 姓名,SC.Cno as 课程号 ,Cname as 课程名,Grade as 成绩 from SC,Student,Course where SC.Sno=Student.Sno AND SC.Cno=Course.Cno AND Cname LIKE '%"+find+"%'order by SC.Cno";



            // sql0="select SC.Sno as 学号,Sname as 姓名,SC.Cno as 课程号 ,Cname as 课程名,Grade as 成绩 from SC,Student,Course where SC.Sno=Student.Sno AND SC.Cno=Course.Cno order by Sage desc";
            }



    }
    modell->setQuery(sql0);
    ui->tableView->setModel(modell);
}


void admin::on_tableView_doubleClicked(const QModelIndex &index)
{
    QAbstractItemModel *model=ui->tableView->model();
     // QSqlQueryModel *model=new QSqlQueryModel;
       QSqlQueryModel *modell=new QSqlQueryModel;
    QModelIndex index1 = ui->tableView->selectionModel()->currentIndex();
    QString sql0;
    row= index.row();
    column=index.column();
  qDebug()<<row;
qDebug()<<column;
QString str=model->data(model->index(row,column)).toString();
if(tt==3)
{
    if(column==4)
    {
      str1=model->data(model->index(row,0)).toString();   //学号
      str2=model->data(model->index(row,2)).toString();   //姓名

      chang=new change;
      chang->show();
    }
}else if(tt==1)
{
    if(column>0){
    str1=model->data(model->index(row,0)).toString();   //学号
    chang=new change;
    chang->show();
    }else {
          QMessageBox::about(NULL,"警告","学号不可修改");
    }
}else if(tt==2)
{
    if(column>0){
    str1=model->data(model->index(row,0)).toString();   //课程号

    chang=new change;
    chang->show();
    }else {
          QMessageBox::about(NULL,"警告","课程号不可修改");
    }
}
}

void admin::on_pushButton_show_4_clicked()
{
    tt=6;
    chang=new change;
    chang->show();

}



