#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include<opencv2/opencv.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QImage cvMatToQImage(const cv::Mat &inMat);
    QPixmap cvMatToQPixmap(const cv::Mat &inMat);

    void onBrowseButtonClicked();
    void onStartButtonClicked();

    std::vector<std::vector<bool>> stringToBooleanVec(std::string str);

    int leastBitAnd(int val, bool bit);
};
#endif // MAINWINDOW_H
