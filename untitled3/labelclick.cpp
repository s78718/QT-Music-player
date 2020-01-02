#include "labelclick.h"

labelclick::labelclick(QLabel *parent):QLabel(parent)
{

}

//重?mousePressEvent事件,??事件?型是不是??了鼠?左?
void labelclick::mousePressEvent(QMouseEvent *event) {
    //如果??了就触?clicked信?
    if (event->button() == Qt::LeftButton) {
        //触?clicked信?
        emit clicked();
    }
    //??事件??父??理
    QLabel::mousePressEvent(event);
}
