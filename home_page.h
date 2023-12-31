#ifndef HOME_PAGE_H
#define HOME_PAGE_H

#include <QMainWindow>

#include <QtSerialPort>
#include <QSerialPortInfo>

#include <QMessageBox>
#include <QString>
#include <QTextStream>

QT_BEGIN_NAMESPACE
namespace Ui {
class home_page;
}
QT_END_NAMESPACE

class home_page : public QMainWindow
{
    Q_OBJECT

public:
    home_page(QWidget *parent = nullptr);
    ~home_page();

private slots:
    void on_pushButton_connect_clicked(bool checked);

    void on_pushButton_serial_clicked();

    void on_pushButton_network_clicked();

    void on_pushButton_clear_clicked();

private:
    Ui::home_page *ui;

    //串口
    QSerialPort *serialPort;
    void Read_Data();
};
#endif // HOME_PAGE_H