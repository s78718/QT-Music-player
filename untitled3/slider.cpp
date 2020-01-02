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

    double percent = X*1.0 /this->width();//�������

    double value = percent*(this->maximum() - this->minimum())+ this->minimum();//��X������צ��h�֤�Ҫ���

    this->setValue(value+0.5);//�`�N �S�B�z�n��b�q������

    //qDebug() << this->sliderPosition();

    QSlider::mousePressEvent(ev_slider);


}
