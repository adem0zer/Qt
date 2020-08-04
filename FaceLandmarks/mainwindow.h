#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <iostream>

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <QGraphicsPixmapItem>

#include <dlib/opencv.h>
#include <dlib/image_io.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_processing.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>


using namespace std;
using namespace cv;
using namespace dlib;


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void update_window();

    void on_btnOpenCamera_clicked();

    void on_btnCloseCamera_clicked();


private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
    QTimer *timer;
    VideoCapture cap;

    Mat frame;
    QImage qt_image;

    void show_frame(Mat &);
    frontal_face_detector detector;
    shape_predictor shape_model;

};
#endif // MAINWINDOW_H
