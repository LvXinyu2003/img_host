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

    //连接按钮
    ui->pushButton_connect->setCheckable(true);
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
        QObject::connect(serialPort, &QSerialPort::readyRead, this, &home_page::Read_Data);
    }
    else
    {
        serialPort->clear();
        serialPort->close();
        ui->pushButton_connect->setText("连接");
        QMessageBox::critical(this, "提示", "串口关闭成功");
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

//读取数据
void home_page::Read_Data()
{
    QByteArray buf;
    buf = serialPort->readAll();
    if(!buf.isEmpty())
    {
        //当前显示内容
        QString str = ui->textBrowser_receive->toPlainText();

        //显示时间戳
        if(ui->checkBox_time->isChecked())
        {
            //获取当前时间
            QDateTime dateTime= QDateTime::currentDateTime();//获取系统当前的时间
            //转为字符
            QString time_str = dateTime .toString("yyyy-MM-dd hh:mm:ss");//格式化时间
            //QTextStream out(stdout);
            //out << time_str;
            //添加时间戳
            str += time_str;
        }

        //添加新内容
        str+=tr(buf);
        //重新显示
        ui->textBrowser_receive->clear();
        ui->textBrowser_receive->append(str);
    }
    buf.clear();
}

//清空
void home_page::on_pushButton_clear_clicked()
{
    ui->textBrowser_receive->clear();
}

