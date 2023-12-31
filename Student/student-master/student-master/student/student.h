#ifndef STUDENT_H
#define STUDENT_H
#include"change.h"
#include <QtSql>
#include <QMainWindow>

namespace Ui {
class student;
}

class student : public QMainWindow
{
    Q_OBJECT

public:
    explicit student(QWidget *parent = 0);
    ~student();
    void init();
    QString stuName;
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::student *ui;
   change *chang;
};

#endif // STUDENT_H
