#include "home_page.h"
#include "ui_home_page.h"

home_page::home_page(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::home_page)
{
    ui->setupUi(this);

    //串口初始化
    serialPort = new QSerialPort(this);
    QStringList serialNamePort;
    foreach (const QSerialPortInfo &inf0, QSerialPortInfo::availablePorts())
    {
        serialNamePort<<inf0.portName();
    }
    ui->comboBox_port->addItems(serialNamePort);
}

home_page::~home_page()
{
    delete ui;
}

//连接
void home_page::on_pushButton_connect_clicked(bool checked)
{
    if(checked)
    {
        /* 串口设置 */
        serialPort->setPortName(ui->comboBox_port->currentText());
        serialPort->setBaudRate(ui->comboBox_baude->currentText().toInt());
        serialPort->setDataBits(QSerialPort::Data8);
        serialPort->setStopBits(QSerialPort::OneStop);
        serialPort->setParity(QSerialPort::NoParity);

        /* 打开串口提示框 */
        if (true == serialPort->open(QIODevice::ReadWrite))
        {
            QMessageBox::information(this, "提示", "串口打开成功");
        }
        else
        {
            QMessageBox::critical(this, "提示", "串口打开失败");
        }
        ui->pushButton_connect->setText("已连接");

        //连接信号槽
        //QObject::connect(serialPort, &QSerialPort::readyRead, this, &MainWindow::Read_Data);
    }
    else
    {
        serialPort->clear();
        serialPort->close();
        ui->pushButton_connect->setText("连接");
    }
}

//串口
void home_page::on_pushButton_serial_clicked()
{
    ui->pushButton_serial->setEnabled(false);
    ui->pushButton_network->setEnabled(true);
    ui->stackedWidget_mode->setCurrentIndex(0);
}

//网络
void home_page::on_pushButton_network_clicked()
{
    ui->pushButton_serial->setEnabled(true);
    ui->pushButton_network->setEnabled(false);
    ui->stackedWidget_mode->setCurrentIndex(1);
}

