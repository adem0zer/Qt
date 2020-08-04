#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QObject>
#include <QTimer>
#include <QProcess>
#include <QPixmap>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    scene = new QGraphicsScene();
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_btnOpenCamera_clicked()
{
    cap.open(0);

    if(!cap.isOpened())  // Check if we succeeded
    {
        cout << "camera is not open" << endl;
    }
    else
    {
        cout << "camera is open" << endl;
        detector = get_frontal_face_detector();
        deserialize("/home/adem/FileFolderPri/shape_predictor_68_face_landmarks.dat") >> shape_model;

        connect(timer, SIGNAL(timeout()), this, SLOT(update_window()));
        timer->start(20);

        ui->btnCloseCamera->setEnabled(true);

    }
}

void MainWindow::on_btnCloseCamera_clicked()
{
    disconnect(timer, SIGNAL(timeout()), this, SLOT(update_window()));
    cap.release();

    Mat image = Mat::zeros(frame.size(),CV_8UC3);

    show_frame(image);

    cout << "camera is closed" << endl;
}


void MainWindow::update_window()
{
    cap >> frame;

    // convert openCV cv::Mat image to dlib::array2d:
    array2d<bgr_pixel> dlib_image;
    assign_image(dlib_image, cv_image<bgr_pixel>(frame));

    std::vector<dlib::rectangle> detected_faces = detector(dlib_image);

    int number_of_detected_faces = detected_faces.size();

    cout << "Number of detected faces : " << number_of_detected_faces << endl;

    std::vector<full_object_detection> shapes;

    //int rect_x, rect_y, rect_w, rect_h;

    for (int i = 0; i < number_of_detected_faces; i++)
    {
        full_object_detection shape = shape_model(dlib_image, detected_faces[i]);

        shapes.push_back(shape);
/*
        rect_x = detected_faces[i].left();
        rect_y = detected_faces[i].top();
        rect_w = detected_faces[i].right() - rect_x;
        rect_h = detected_faces[i].bottom() - rect_y;

        Rect face_rectangle(rect_x, rect_y, rect_w, rect_h);

        cv::rectangle(frame, face_rectangle, Scalar( 0, 255, 0 ), 3, 8, 0);
*/
        for (int j = 0; j < 68; j++)
        {
            circle(frame, Point(shape.part(j).x(), shape.part(j).y()), 2, Scalar( 0, 0, 255 ), 1, LINE_AA );
        }
    }

    show_frame(frame);
}

void MainWindow::show_frame(Mat &image)
{
    Mat resized_image = image.clone();

    int width_of_label = ui->graphicsView->width();
    int height_of_label = ui->graphicsView->height();

    Size size(width_of_label, height_of_label);

    cv::resize(image, resized_image, size);

    cvtColor(resized_image, resized_image, COLOR_BGR2RGB);

    QImage qt_image((const unsigned char*) (resized_image.data), resized_image.cols, resized_image.rows, QImage::Format_RGB888);

    //ui->graphicsView->setPixmap(QPixmap::fromImage(qt_image));

    ui->graphicsView->setScene(scene);
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(qt_image));
    scene->addItem(item);
    ui->graphicsView->show();

}

