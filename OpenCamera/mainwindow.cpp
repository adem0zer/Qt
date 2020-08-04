#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsPixmapItem>
#include <QTimer>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene();

    timer = new QTimer(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::open_video()
{
    cap >> frame;
    Mat resized_image = frame.clone();

    int width_of_label = ui->graphicsView->width();
    int height_of_label = ui->graphicsView->height();

    Size size(width_of_label, height_of_label);

    cv::resize(resized_image, resized_image, size);

    cvtColor(resized_image, resized_image, COLOR_BGR2RGB);

    QImage qt_image((const unsigned char*) (resized_image.data), resized_image.cols, resized_image.rows, QImage::Format_RGB888);

    //ui->lbl->setPixmap(QPixmap::fromImage(qt_image));

    ui->graphicsView->setScene(scene);
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(qt_image));
    scene->addItem(item);
    ui->graphicsView->show();

}

void MainWindow::close_video()
{
    cap.release ();
}

void MainWindow::on_btnClose_clicked()
{
    close_video();
}

void MainWindow::on_btnOpen_clicked()
{
    cap.open(0);

    if(!cap.isOpened())  // Check if we succeeded
    {
        cout << "camera is not open" << endl;
    }
    else
    {
        cout << "camera is open" << endl;

        connect(timer, SIGNAL(timeout()), this, SLOT(open_video()));
        timer->start(20);

        ui->btnClose->setEnabled(true);

    }
}
