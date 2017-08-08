#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QDebug>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->image->setVisible(false);
    ui->image->setAlignment(Qt::AlignCenter);
    //cout << "run here" << a->isNull();  debug用!
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_open_clicked()
{
    a = new QImage;
    QString FilePath = QFileDialog::getOpenFileName(this,tr("Open File"),"/",tr("Images (*.png *.jpg)"));
    a->load(FilePath);
    if(a->isNull()) {QMessageBox::information(this,"Error!!!","Need a image file!");}
    if(!a->isNull()){
        Image = new QImage;
        Image=a;
        pixmap = QPixmap::fromImage(*Image);
        ui->image->show();
        ui->image->setPixmap(pixmap.scaled(ui->image->width(),ui->image->height(),Qt::KeepAspectRatio));
    }
}

void MainWindow::on_origin_clicked()
{
    if(ui->image->isVisible()){
        pixmap = QPixmap::fromImage(*Image);
        ui->image->setPixmap(pixmap.scaled(ui->image->width(),ui->image->height(),Qt::KeepAspectRatio));
    }
}

void MainWindow::on_gray_clicked()
{
    if(ui->image->isVisible()){
        QImage grayscale = *Image;
        QRgb val;
        QColor oldColor;
        for(int x=0;x<grayscale.width();x++){
            for(int y=0;y<grayscale.height();y++){
                oldColor = QColor(grayscale.pixel(x,y));
                int ave = (oldColor.red()+oldColor.green()+oldColor.blue())/3;
                val = qRgb(ave,ave,ave);
                grayscale.setPixel(x,y,val);
            }
        }
        pixmap = QPixmap::fromImage(grayscale);
        ui->image->setPixmap(pixmap.scaled(ui->image->width(),ui->image->height(),Qt::KeepAspectRatio));
    }
}

void MainWindow::on_invert_clicked()
{
    if(ui->image->isVisible()){
        QImage invert = *Image;
        QRgb val;
        QColor oldColor;
        for(int x=0;x<invert.width();x++){
            for(int y=0;y<invert.height();y++){
                oldColor = QColor(invert.pixel(x,y));
                val = qRgb(255-oldColor.red(),255-oldColor.green(),255-oldColor.blue());
                //val = qRgb(oldColor.blue(),oldColor.red(),oldColor.green());
                invert.setPixel(x,y,val);
            }
        }
        pixmap = QPixmap::fromImage(invert);
        ui->image->setPixmap(pixmap.scaled(ui->image->width(),ui->image->height(),Qt::KeepAspectRatio));
    }
}

void MainWindow::on_blurry_clicked()
{
    if(ui->image->isVisible()){
        QImage blurry =*Image;
        QRgb val;
        QColor oldColor1, oldColor2, oldColor3, oldColor4, oldColor5, oldColor6, oldColor7, oldColor8, oldColor9;
        int width = blurry.width(), height = blurry.height();
        if(blurry.width()%3 == 0) {width = width;}
        if(blurry.width()%3 == 1) {width = width-1;}
        if(blurry.width()%3 == 2) {width = width-2;}
        if(blurry.height()%3 == 0) {height = height;}
        if(blurry.height()%3 == 1) {height = height-1;}
        if(blurry.height()%3 == 2) {height = height-2;}
        for(int x=0;x<width;x=x+3){
            for(int y=0; y<height;y=y+3){
                oldColor1 = QColor(blurry.pixel(x,y));
                oldColor2 = QColor(blurry.pixel(x,y+1));
                oldColor3 = QColor(blurry.pixel(x,y+2));
                oldColor4 = QColor(blurry.pixel(x+1,y));
                oldColor5 = QColor(blurry.pixel(x+1,y+1));
                oldColor6 = QColor(blurry.pixel(x+1,y+2));
                oldColor7 = QColor(blurry.pixel(x+2,y));
                oldColor8 = QColor(blurry.pixel(x+2,y+1));
                oldColor9 = QColor(blurry.pixel(x+2,y+2));
                int oldColorr[9] = {oldColor1.red(), oldColor2.red(), oldColor3.red(), oldColor4.red(),  oldColor5.red(), oldColor6.red(), oldColor7.red(), oldColor8.red(), oldColor9.red()};
                int oldColorg[9] = {oldColor1.green(), oldColor2.green(), oldColor3.green(), oldColor4.green(),  oldColor5.green(), oldColor6.green(), oldColor7.green(), oldColor8.green(), oldColor9.green()};
                int oldColorb[9] = {oldColor1.blue(), oldColor2.blue(), oldColor3.blue(), oldColor4.blue(),  oldColor5.blue(), oldColor6.blue(), oldColor7.blue(), oldColor8.blue(), oldColor9.blue()};
                int red = 0, green = 0, blue = 0;
                for(int i=0;i<9;i++) {red = red + oldColorr[i];}
                for(int i=0;i<9;i++) {green = green + oldColorg[i];}
                for(int i=0;i<9;i++) {blue = blue + oldColorb[i];}
                val = qRgb(red/9,green/9,blue/9);
                blurry.setPixel(x,y,val);
                blurry.setPixel(x,y+1,val);
                blurry.setPixel(x,y+2,val);
                blurry.setPixel(x+1,y,val);
                blurry.setPixel(x+1,y+1,val);
                blurry.setPixel(x+1,y+2,val);
                blurry.setPixel(x+2,y,val);
                blurry.setPixel(x+2,y+1,val);
                blurry.setPixel(x+2,y+2,val);
            }
        }
        pixmap = QPixmap::fromImage(blurry);
        ui->image->setPixmap(pixmap.scaled(ui->image->width(),ui->image->height(),Qt::KeepAspectRatio));
    }
}

void MainWindow::on_save_clicked()
{
    if(ui->image->isVisible()){
        newimage = new QImage;
        QString ImagePath = QFileDialog::getSaveFileName(this,tr("Save Filr"),"/",tr("PNG(*.png);;JPG(*.jpg)"));
        *newimage = pixmap.toImage();
        newimage->save(ImagePath);
    }
}

void MainWindow::on_clear_clicked()
{
    if(ui->image->isVisible()){
    ui->image->clear();
    delete Image;
    ui->image->setVisible(false);
    }
}
