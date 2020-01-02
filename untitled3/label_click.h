#ifndef LABEL_CLICK_H
#define LABEL_CLICK_H

#include <QWidget>
#include <QMouseEvent>
#include <QLabel>


class label_click : public QLabel
{
    Q_OBJECT

public:
    explicit label_click(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *ev_label) override;

signals:

    void mousepress();
    void mousepress_right();

public slots:
};

#endif // LABEL_CLICK_H
