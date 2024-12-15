#include "suspendwindow.h"

SuspendWindow::SuspendWindow(QWidget *parent, QPixmap pix)
    : QWidget{parent}
{
    setWindowFlags(Qt::FramelessWindowHint|Qt::SubWindow);
    setAttribute(Qt::WA_TranslucentBackground);
    QGraphicsDropShadowEffect *gra=new QGraphicsDropShadowEffect;
    gra->setColor(Qt::green);
    gra->setOffset(0,0);
    gra->setBlurRadius(30);

    setMinimumSize(pix.width()+6,pix.height()+6);

    label=new QLabel(this);
    label->setPixmap(pix);
    label->setScaledContents(1);

    QHBoxLayout *qhb=new QHBoxLayout(this);
    qhb->setContentsMargins(3,3,3,3);
    qhb->addWidget(label);

    label->setGraphicsEffect(gra);
}

void SuspendWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        isleft=true;
        wp=pos();
        p=event->globalPosition().toPoint();
    }
}

void SuspendWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(isleft)
    {
        move(wp+event->globalPosition().toPoint()-p);
    }
}

void SuspendWindow::mouseReleaseEvent(QMouseEvent *event)
{
    isleft=false;
}
