#ifndef CHANGE_H
#define CHANGE_H

#include <QMainWindow>

namespace Ui {
class change;
}

class change : public QMainWindow
{
    Q_OBJECT

public:
    explicit change(QWidget *parent = nullptr);
    ~change();

private slots:
    void on_pushButton_dele_clicked();

    void on_pushButton_exit_clicked();

private:
    Ui::change *ui;
};

#endif // CHANGE_H
