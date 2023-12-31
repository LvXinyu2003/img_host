#ifndef COURSE_H
#define COURSE_H

#include <QMainWindow>

namespace Ui {
class course;
}

class course : public QMainWindow
{
    Q_OBJECT

public:
    explicit course(QWidget *parent = 0);
    ~course();

private slots:
    void on_pushButton_exit_clicked();

    void on_pushButton_enter_clicked();

private:
    Ui::course *ui;
};

#endif // COURSE_H
