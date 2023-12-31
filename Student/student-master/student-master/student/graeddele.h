#ifndef GRAEDDELE_H
#define GRAEDDELE_H

#include <QMainWindow>

namespace Ui {
class graeddele;
}

class graeddele : public QMainWindow
{
    Q_OBJECT

public:
    explicit graeddele(QWidget *parent = nullptr);
    ~graeddele();

private slots:
    void on_pushButton_exit_clicked();

    void on_pushButton_dele_clicked();

private:
    Ui::graeddele *ui;
};

#endif // GRAEDDELE_H
