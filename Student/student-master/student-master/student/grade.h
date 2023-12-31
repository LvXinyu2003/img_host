#ifndef GRADE_H
#define GRADE_H

#include <QMainWindow>

namespace Ui {
class grade;
}

class grade : public QMainWindow
{
    Q_OBJECT

public:
    explicit grade(QWidget *parent = nullptr);
    ~grade();

private slots:
    void on_pushButton_exit_clicked();

    void on_pushButton_enter_clicked();

private:
    Ui::grade *ui;
};

#endif // GRADE_H
