#ifndef SLIDER_H
#define SLIDER_H

#include <QWidget>
#include <QObject>
#include <QSlider>
#include <QMouseEvent>

class slider : public QSlider
{
public:

    slider(QWidget *parent = nullptr);
    ~slider();
    void mousePressEvent(QMouseEvent *ev_slider);

};

#endif // SLIDER_H
