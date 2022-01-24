#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

int IMAGE_SIZE = 400;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->browseButton, &QPushButton::clicked, this, &MainWindow::onBrowseButtonClicked);
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::onStartButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onBrowseButtonClicked()
{
    QString s1 =
        QFileDialog::getOpenFileName(this, "Open a file", "directoryToOpen",
            "Images (*.png *.xpm *.jpg *.tif)");
    ui->lineEdit->setText(s1);
}

void MainWindow::onStartButtonClicked()
{
    if(ui->lineEdit->displayText().isEmpty() || ui->textEdit->displayText().isEmpty()){
        QMessageBox msg;
        msg.setText("Complete informations!");
        msg.exec();
        return;
    }
    cv::Mat image = cv::imread(ui->lineEdit->displayText().toStdString());
    ui->imageBefore->setPixmap(cvMatToQPixmap(image).scaled(IMAGE_SIZE,IMAGE_SIZE));
    std::string txt = ui->textEdit->displayText().toStdString();
    auto bits = stringToBooleanVec(txt);

    int x = 0;
    int y = 0;
    cv::Mat imageAfter;
    cv::resize(image, imageAfter, cv::Size(400, 400), cv::INTER_LINEAR);
    cv::Mat imageBefore;
    cv::resize(image, imageBefore, cv::Size(400, 400), cv::INTER_LINEAR);
    for(int i = 0;i < IMAGE_SIZE; ++i){
        for(int j = 0;j < IMAGE_SIZE; ++j){
            auto pixel = imageAfter.at<cv::Vec3b>(i, j);
            if(x == 8){
                ++y;
                x = 0;
            }
            y %= bits.size();
            int r = pixel.val[0] + leastBitAnd(pixel.val[0], bits[y][x]);
            ++x;
            if(x == 8){
                ++y;
                x = 0;
            }
            y %= bits.size();
            int g = pixel.val[1] + leastBitAnd(pixel.val[1], bits[y][x]);
            ++x;
            if(x == 8){
                ++y;
                x = 0;
            }
            y %= bits.size();
            int b = pixel.val[2] + leastBitAnd(pixel.val[2], bits[y][x]);
            ++x;
            imageAfter.at<cv::Vec3b>(i, j) = cv::Vec3b(r, g, b);
        }
    }

    ui->imageAfter->setPixmap(cvMatToQPixmap(imageAfter));
    for(int i = 0;i < 10; ++i){
        for(int j = 0; j < 10; ++j){
            if(imageAfter.at<cv::Vec3b>(i,j).val[1] != imageBefore.at<cv::Vec3b>(i,j).val[1]){
                qDebug() << "Image[" << i <<"]" << "[" << j << "].green after" << imageAfter.at<cv::Vec3b>(i,j).val[1] ;
                qDebug() << "Image[" << i <<"]" << "[" << j << "].green before" << imageBefore.at<cv::Vec3b>(i,j).val[1] ;
                qDebug() << "-------------------------------------------------------------------------------------";
            }
        }
    }


}

QImage MainWindow::cvMatToQImage(const cv::Mat &inMat)
{
  switch ( inMat.type() )
  {
     // 8-bit, 4 channel
     case CV_8UC4:
     {
        QImage image( inMat.data,
                      inMat.cols, inMat.rows,
                      static_cast<int>(inMat.step),
                      QImage::Format_ARGB32 );

        return image;
     }

     // 8-bit, 3 channel
     case CV_8UC3:
     {
        QImage image( inMat.data,
                      inMat.cols, inMat.rows,
                      static_cast<int>(inMat.step),
                      QImage::Format_RGB888 );

        return image.rgbSwapped();
     }

     // 8-bit, 1 channel
     case CV_8UC1:
     {
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
        QImage image( inMat.data,
                      inMat.cols, inMat.rows,
                      static_cast<int>(inMat.step),
                      QImage::Format_Grayscale8 );
#else
        static QVector<QRgb>  sColorTable;

        // only create our color table the first time
        if ( sColorTable.isEmpty() )
        {
           sColorTable.resize( 256 );

           for ( int i = 0; i < 256; ++i )
           {
              sColorTable[i] = qRgb( i, i, i );
           }
        }

        QImage image( inMat.data,
                      inMat.cols, inMat.rows,
                      static_cast<int>(inMat.step),
                      QImage::Format_Indexed8 );

        image.setColorTable( sColorTable );
#endif

        return image;
     }

     default:
        qWarning() << "ASM::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type();
        break;
  }

  return QImage();
}

QPixmap MainWindow::cvMatToQPixmap(const cv::Mat &inMat)
{
    return QPixmap::fromImage( cvMatToQImage( inMat ) );
}

std::vector<std::vector<bool>> MainWindow::stringToBooleanVec(std::string str)
{
    std::vector<std::vector<bool>> result;
    for(auto const& c : str){
        std::vector<bool> chr;
        int k = c;
        for(int i = 0;i < 8; ++i){
            chr.push_back(k % 2);
            k /= 2;
        }
        result.push_back(chr);
    }
    return result;
}

int MainWindow::leastBitAnd(int val, bool bit)
{
    if(val % 2 == 1 && !bit){
        return -1;
    }
    if(val % 2 == 0 && bit){
        return 1;
    }
    return 0;
}
