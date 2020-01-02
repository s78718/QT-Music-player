#include "label_click.h"

label_click::label_click(QWidget *parent) : QLabel(parent)
{

}

void label_click::mousePressEvent(QMouseEvent *ev_label)
{


    if(ev_label->buttons() == Qt::LeftButton)
    {
        emit mousepress();

    }

    else if (ev_label->buttons() == Qt::RightButton)

    {
        emit mousepress_right();
    }
}
