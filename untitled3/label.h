#ifndef LABEL_H
#define LABEL_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QEvent>

class label : public QLabel
{
public:
    label();

     void mousePressEvent(QMouseEvent *ev);


signals:

        void Mouse_Pressed();
};

#endif // LABEL_H
