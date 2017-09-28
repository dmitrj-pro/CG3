#include "drawimage.h"
#include "ui_drawimage.h"
#include "graphiccore.h"

#include <iostream>


DrawImage::DrawImage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DrawImage)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->horizontalLayoutWidget);
    connect(ui->BrushColor, SIGNAL (released()),this, SLOT (brushColor()));
    connect(ui->drawCoor, SIGNAL (released()),this, SLOT (drawColor()));
    connect(ui->horizontalSlider, SIGNAL (valueChanged(int)), this, SLOT(changeWidth(int)));
    connect(ui->checkBox, SIGNAL (toggled(bool)), this, SLOT(changeRem(bool)));
    connect(ui->graphicsView, SIGNAL(Success(QString)), this, SLOT(DrawNewImage(QString)));
    //connect(ui->graphicsView, SIGNAL(mousePressEvent(QMouseEvent*)), this, SLOT(mousePressEvent(QMouseEvent*)));
}

void DrawImage::changeRem(bool val){
    ui->graphicsView->Lock(!val);
}

void DrawImage::DrawNewImage(QString file){
    showImage(ui->graphicsView_2, file);
}

void DrawImage::changeWidth(int w){
    ui->graphicsView->setWidth(w);
}

void DrawImage::brushColor(){
    if (ui->checkBox_2->isChecked()){
        QString fil;
        getUserFile(fil);
        ui->graphicsView->setDrawFile(fil);
    } else {
        getUsetColor(_brushColor);
        ui->graphicsView->setColor(_brushColor);
    }
}
void DrawImage::drawColor(){
    getUsetColor(_drawColor);
    ui->graphicsView->setDrawColor(_drawColor);
}


DrawImage::~DrawImage()
{
    delete ui;
}
