#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QImage>
#include <QPixmap>
#include <QString>
#include <QFile>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_open_clicked();

    void on_gray_clicked();

    void on_invert_clicked();

    void on_save_clicked();

    void on_clear_clicked();

    //void on_pushButton_clicked();

    void on_origin_clicked();

    void on_blurry_clicked();

private:
    Ui::MainWindow *ui;
    QPixmap pixmap;
    QImage *Image;
    QImage *a;
    QImage *newimage;
};

#endif // MAINWINDOW_H
