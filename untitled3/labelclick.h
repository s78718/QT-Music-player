#ifndef LABELCLICK_H
#define LABELCLICK_H

#include <QLabel>
#include <QMouseEvent>

class labelclick : public QLabel
{
    Q_OBJECT
public:
    explicit labelclick(QLabel *parent = 0);
protected:
    //重?mousePressEvent事件
    virtual void mousePressEvent(QMouseEvent *event);

signals:
    //自定?clicked()信?,在mousePressEvent事件?生?触?
    void clicked();

public slots:

};


#endif // LABELCLICK_H
