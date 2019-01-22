
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QThread>
#include <QPainter>
#include <QInputDialog>
#include <QtMath>

#include<iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
   ui(new Ui::MainWindow)
{ 
	
    ui->setupUi(this);

    mPlayer = new VideoPlayer;
    connect(mPlayer,SIGNAL(sig_GetOneFrame(QImage)),this,SLOT(slotGetOneFrame(QImage)));

    connect(mPlayer,SIGNAL(sig_GetRFrame(QImage)),this,SLOT(slotGetRFrame(QImage)));

    connect(ui->Open_red,&QAction::triggered,this,&MainWindow::slotOpenRed);
    connect(ui->Close_Red,&QAction::triggered,this,&MainWindow::slotCloseRed);

    mPlayer->startPlay();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.setBrush(Qt::white);
    painter.drawRect(0, 0, this->width(), this->height()); //先画成白色

    if (mImage.size().width() <= 0) return;

    //将图像按比例缩放成和窗口一样大小
    QImage img = mImage.scaled(this->size(),Qt::KeepAspectRatio);

    int x = this->width() - img.width();
    int y = this->height() - img.height();

    x /= 2;
    y /= 2;

    painter.drawImage(QPoint(x,y),img); //画出图像

    if(open_red==true){

    QWidget *red_video=new QWidget(this);
    red_video->resize(this->width()/3,this->height()/3);

    //提取出图像中的R数据
    painter.setBrush(Qt::white);
    painter.drawRect(0, 0, red_video->width(),red_video->height()); //先画成白色

    if (R_mImage.size().width() <= 0) return;

    //将图像按比例缩放成和窗口一样大小
    QImage R_img = R_mImage.scaled(red_video->size(),Qt::KeepAspectRatio);

    int R_x = red_video->width() - R_img.width();
    int R_y = red_video->height() - R_img.height();

    R_x /= 2;
    R_y /= 2;

    painter.drawImage(QPoint(R_x,R_y),R_img);  //画出图像
    }
}

void MainWindow::slotGetOneFrame(QImage img)
{
    mImage = img;
    update(); //调用update将执行 paintEvent函数
}
//显示二值图像
QImage Indentificate(QImage image)
{
	QSize size = image.size();
	QImage binaryImage(size, QImage::Format_RGB32);
	int width = image.width(), height = image.height();
	int threshold = 200;
	for (int i = 0; i<width; i++)
		for (int j = 0; j < height; j++)
		{
			QRgb pixel = image.pixel(i, j);
			int r = qRed(pixel) * 0.3;
			int g = qGreen(pixel) * 0.59;
			int b = qBlue(pixel) * 0.11;
			int rgb = r + g + b;        //先把图像灰度化，转化为灰度图像
			if (rgb > threshold)        //然后按某一阀值进行二值化
				rgb = 255;
			else
				rgb = 0;
			QRgb newPixel = qRgb(rgb, rgb, rgb);
			binaryImage.setPixel(i, j, newPixel);
		}
	return binaryImage;
}
//小窗口显示
void MainWindow::slotGetRFrame(QImage img)
{
    R_mImage = img;
    //在新线程中执行显示二值图像函数
	//QFuture<QImage> future = QtConcurrent::run(Indentificate, mImage);
	//R_mImage = future.result();
    update(); //调用update将执行 paintEvent函数
}
//显示图像红色通道
bool MainWindow::slotOpenRed()
{
    open_red=true;
    return open_red;
}
//关闭图像红色通道
bool MainWindow::slotCloseRed()
{
    open_red=false;
    return open_red;
}



