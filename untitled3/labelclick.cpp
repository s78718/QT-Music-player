#include "labelclick.h"

labelclick::labelclick(QLabel *parent):QLabel(parent)
{

}

//��?mousePressEvent�ƥ�,??�ƥ�?���O���O??�F��?��?
void labelclick::mousePressEvent(QMouseEvent *event) {
    //�p�G??�F�N�D?clicked�H?
    if (event->button() == Qt::LeftButton) {
        //�D?clicked�H?
        emit clicked();
    }
    //??�ƥ�??��??�z
    QLabel::mousePressEvent(event);
}
