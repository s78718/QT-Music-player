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
    //��?mousePressEvent�ƥ�
    virtual void mousePressEvent(QMouseEvent *event);

signals:
    //�۩w?clicked()�H?,�bmousePressEvent�ƥ�?��?�D?
    void clicked();

public slots:

};


#endif // LABELCLICK_H
