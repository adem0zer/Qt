#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <opencv2/imgproc.hpp>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
using namespace cv;
using namespace std;

class QGraphicsScene;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    void close_video();

private slots:
    void on_btnClose_clicked();

    void on_btnOpen_clicked();
    void open_video();

private:
    Ui::MainWindow *ui;
    Mat frame;
    VideoCapture cap;
    QTimer *timer;
    QGraphicsScene* scene;
};
#endif // MAINWINDOW_H
