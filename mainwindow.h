
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QPaintEvent>
#include <QWidget>
#include <QtDebug>

#include <QtConcurrent/qtconcurrentrun.h>
#include "videoplayer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //QImage Indentificate(QImage img);    //显示二值图像

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::MainWindow *ui;

    VideoPlayer *mPlayer;                  //播放线程

    QImage mImage;                         //记录当前的图像
    QImage R_mImage;

    QString url; 

    bool open_red=false;

private slots:
    void slotGetOneFrame(QImage img);
    void slotGetRFrame(QImage img);
    bool slotOpenRed();
    bool slotCloseRed();
};

#endif // MAINWINDOW_H
