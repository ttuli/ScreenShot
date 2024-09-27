#include "capturerec.h"

CaptureRec::CaptureRec(QWidget *parent,int ScreenW,int ScreenH)
    : QWidget{parent}
{
    resize(0,0);
    setAttribute(Qt::WA_TranslucentBackground);
    ScreenWidth=ScreenW;
    ScreenHeight=ScreenH;
}

void CaptureRec::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        isleft=true;
        wp=pos();
        p=event->globalPosition().toPoint();
    }
}

void CaptureRec::mouseMoveEvent(QMouseEvent *event)
{
    if(isleft&&!isAtBorder)
    {
        QPoint delta=event->globalPosition().toPoint()-p;
        emit moveSig();
        move(qMax(0,(wp+delta).x()),qMax(0,(wp+delta).y()));
        if((wp+delta).x()+width()>ScreenWidth||(wp+delta).y()+height()>ScreenHeight)
        {
            move(qMin(ScreenWidth-width(),qMax(0,(wp+delta).x())),qMin(ScreenHeight-height(),qMax(0,(wp+delta).y())));
        }
    }
}

void CaptureRec::mouseReleaseEvent(QMouseEvent *event)
{
    isleft=false;
    isAtBorder=false;
}

void CaptureRec::enterEvent(QEnterEvent *event)
{
    setCursor(Qt::SizeAllCursor);
}

void CaptureRec::leaveEvent(QEvent *event)
{
    setCursor(Qt::ArrowCursor);
}
