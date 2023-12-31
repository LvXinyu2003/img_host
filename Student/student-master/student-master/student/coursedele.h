#ifndef COURSEDELE_H
#define COURSEDELE_H

#include <QMainWindow>

namespace Ui {
class coursedele;
}

class coursedele : public QMainWindow
{
    Q_OBJECT

public:
    explicit coursedele(QWidget *parent = nullptr);
    ~coursedele();

private slots:
    void on_pushButton_exit_clicked();

    void on_pushButton_dele_clicked();

private:
    Ui::coursedele *ui;
};

#endif // COURSEDELE_H
