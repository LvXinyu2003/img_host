#ifndef ADMIN_H
#define ADMIN_H
#include"admin_change.h"
#include <QMainWindow>
#include"dele.h"
#include"course.h"
#include"coursedele.h"
#include"grade.h"
#include"graeddele.h"
#include"change.h"
#include <QtSql>
namespace Ui {
class admin;
}

class admin : public QMainWindow
{
    Q_OBJECT

public:
    explicit admin(QWidget *parent = 0);
    ~admin();
    void init();

     Qt::ItemFlags flags(const QModelIndex &) const ;//必须有这句，否则无法手动修改模型内容
private slots:
    void on_pushButton_exit_clicked();

    void on_pushButton_show_clicked();//学生信息

    void on_pushButton_show_2_clicked();//课程信息

   void on_pushButton_show_3_clicked();//成绩信息

    void on_pushButton_change_clicked();

    void on_pushButton_del_clicked();
    void find();
    void on_pushButton_order_clicked();






    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_pushButton_show_4_clicked();

private:
    Ui::admin *ui;
    admin_change *adminc;
    dele *del;
    course *cour;
    coursedele *courdele;
    grade *grad;
    graeddele *gradele;
    change *chang;
};

#endif // ADMIN_H
