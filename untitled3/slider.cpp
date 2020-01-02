#include "slider.h"
#include <QMouseEvent>
#include <QDebug>
#include <QCoreApplication>

slider::slider(QWidget *parent):QSlider (parent)

{

}

slider::~slider()
{


}

void slider::mousePressEvent(QMouseEvent *ev_slider)
{


    int X = ev_slider->pos().x();

    double percent = X*1.0 /this->width();//控件長度

    double value = percent*(this->maximum() - this->minimum())+ this->minimum();//算出控件長度佔多少比例長度

    this->setValue(value+0.5);//注意 沒處理好後半段不能拖行

    //qDebug() << this->sliderPosition();

    QSlider::mousePressEvent(ev_slider);


}
