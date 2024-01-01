#include "home_page.h"
#include "ui_home_page.h"


int img_width = 188;
int img_height = 120;
int img_size = img_width*img_height;
int Paint_Mode = 0;

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
    ui->pushButton_img_trans->setCheckable(true);
}

home_page::~home_page()
{
    delete ui;
}

//串口连接
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
        QMessageBox::information(this, "提示", "串口关闭成功");
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

    //QTextStream out(stdout);
    //out << buf;
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
            str += " ";
        }

        //hex显示
        if(ui->checkBox_hex_display->isChecked())
        {
            str+=buf.toHex();
        }
        //文本显示
        else
        {
            //添加新内容
            str+=tr(buf);
        }

        //重新显示
        ui->textBrowser_receive->clear();
        ui->textBrowser_receive->append(str);
    }
    buf.clear();
}

int cnt = 0;
QTextStream out(stdout);
QVector<int> img_vec(img_size);
int length_sum = 0;
//接收图像
void home_page::Read_Img()
{

    QByteArray buf;
    QString str;

    buf = serialPort->readAll();
    if(!buf.isEmpty())
    {

        str += buf.toHex();
        //out<<str<<"\r\n";
        //帧头
        if(str[0]=='6' && str[1] == '6' && str[2] == 'f' && str[3] == 'f' && str[4] == '0' && str[5] == '1' && str[6] == '0' && str[7] == '1')
        {
            out<<"length_sum:"<<length_sum<<"\r\n";
            length_sum=0;
            length_sum+=str.length();
            // out<<"header,length:"<<str.length();
            // out<<str<<"\r\n";
            str.remove(0,7);

            cnt = 0;
            for(int i = 0;i<=str.length()-8-2;i+=2)
            {
                QString tem1 = str[i];
                QString tem2 = str[i+1];
                bool ok;
                int tem_int1 = tem1.toInt(&ok,16);
                int tem_int2 = tem2.toInt(&ok,16);
                int value = tem_int1*16 + tem_int2;

                img_vec[cnt] = value;
                cnt++;
            }

            // for (auto num=img_vec.begin(); num!=img_vec.end()-1; num++)
            // {
            //     out<< *num;
            // }
            // out<<"\r\n";
        }
        //非帧头
        else
        {
            length_sum+=str.length();
            // out<<"length:"<<str.length();
            // out<<str<<"\r\n";
            for(int i = 0;i<=str.length()-2;i+=2)
            {
                QString tem1 = str[i];
                QString tem2 = str[i+1];
                bool ok;
                int tem_int1 = tem1.toInt(&ok,16);
                int tem_int2 = tem2.toInt(&ok,16);
                int value = tem_int1*16 + tem_int2;

                img_vec[cnt] = value;
                cnt++;
            }
        }
    }
    buf.clear();


}

//绘图
void home_page::paintEvent(QPaintEvent *event)
{
    //1为绘制 0为擦除
    if(Paint_Mode == 1)
    {
        Q_UNUSED(event);
        //绘图前准备画笔、画刷
        QPen pen; //画笔。绘制图形边线，由颜色、宽度、线风格等参数组成
        QColor color_white;
        color_white.setRgb(0,0,0);
        QColor color_black;
        color_black.setRgb(255,255,255);
        pen.setColor(color_white);

        QPainter painter(this);   //可在QPaintDevice上绘制各种图形。QPaintDevice有之类QWidget、QImage、QOpenGLPaintDevice等
        painter.setPen(pen);
        //painter.drawLine(QPoint(0,0),QPoint(this->rect().width()*1/2,this->rect().height()*3/4));   //QPainter绘制直线

        QPoint x1(this->rect().width()*1/2,this->rect().height()*1/12);
        QPoint x2(x1.x()+img_width,this->rect().height()*1/12);
        QPoint x3(this->rect().width()*1/2,this->rect().height()*1/12+img_height);
        QPoint x4(this->rect().width()*1/2+img_width,this->rect().height()*1/12+img_height);
        painter.drawLine(x1,x2);
        painter.drawLine(x1,x3);
        painter.drawLine(x3,x4);
        painter.drawLine(x2,x4);

        Paint_Mode = 0;
    }

}

//清空
void home_page::on_pushButton_clear_clicked()
{
    ui->textBrowser_receive->clear();

    //绘图
    Paint_Mode = 1;
    QWidget::repaint();
}

//擦除画面
void home_page::on_pushButton_clear_img_clicked()
{
    //擦除
    Paint_Mode = 0;
    QPainter painter(this);
    painter.eraseRect(this->rect());
    QWidget::repaint();
}

//图传连接
void home_page::on_pushButton_img_trans_clicked(bool checked)
{
    if(checked)
    {
        //图像大小设置
        img_height = ui->lineEdit_img_height->text().toInt();
        img_width = ui->lineEdit_img_width->text().toInt();
        img_size = img_width*img_height;
        QTextStream out(stdout);
        out << img_height;
        out << img_width;

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
        QObject::connect(serialPort, &QSerialPort::readyRead, this, &home_page::Read_Img);
    }
    else
    {
        serialPort->clear();
        serialPort->close();
        ui->pushButton_connect->setText("连接");
        QMessageBox::information(this, "提示", "串口关闭成功");
    }
}

