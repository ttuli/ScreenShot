#include "capturerec.h"

CaptureRec::CaptureRec(QWidget *parent,int ScreenW,int ScreenH)
    : QWidget{parent}
{
    resize(0,0);
    setAttribute(Qt::WA_TranslucentBackground);
    ScreenWidth=ScreenW;
    ScreenHeight=ScreenH;

    currentChoice=CHOICE_CURSOR;
    pix=new QPixmap();

    colorDia=new ColorSelectionInterface(parent);
}

void CaptureRec::setCurrentChoice(int choice)
{
    currentChoice=choice;
    if(choice==CHOICE_CURSOR)
    {
        if(!hasDraw)
        {
            pix=new QPixmap();
            update();
            emit updateSig();
        }
    }
    else if(choice==CHOICE_DRAW)
    {
        if(pix->isNull())
        {
            currentPix=QGuiApplication::primaryScreen()->grabWindow(0,x(),y(),width(),height());
            pix=&currentPix;

            QPainter painter;
            painter.begin(pix);
            painter.drawPixmap(0,0,width(),height(),*pix);
            painter.end();
            update();
        }
    }
    else if(choice==CHOICE_LINE)
    {
        if(pix->isNull())
        {
            currentPix=QGuiApplication::primaryScreen()->grabWindow(0,x(),y(),width(),height());
            pix=&currentPix;

            // QPainter painter;
            // painter.begin(pix);
            // painter.drawPixmap(0,0,width(),height(),*pix);
            // painter.end();
            update();
        }
    }
}


int CaptureRec::getCurrentChoice()
{
    return currentChoice;
}

void CaptureRec::mousePressEvent(QMouseEvent *event)
{
    if(currentChoice==CHOICE_DRAW||currentChoice==CHOICE_LINE)
    {
        startP=event->pos();
        currentP=event->pos();
        pix_copy=pix->copy(pix->rect());
        return;
    }

    if(event->button()==Qt::LeftButton&&!hasDraw)
    {
        isleft=true;
        wp=pos();
        p=event->globalPosition().toPoint();
    }
}

void CaptureRec::mouseMoveEvent(QMouseEvent *event)
{
    if(currentChoice==CHOICE_DRAW)
    {
        preP=currentP;
        hasDraw=true;
        currentP=event->pos();
        QPainter painter;
        painter.begin(pix);
        QPen pen;
        pen.setWidth(2);
        pen.setColor(Qt::green);
        painter.setPen(pen);
        painter.drawLine(preP,currentP);
        painter.end();
        update();
        return;
    }
    else if(currentChoice==CHOICE_LINE)
    {
        *pix=pix_copy.copy(pix_copy.rect());
        hasDraw=true;
        QPainter painter;
        QPen pen;
        pen.setWidth(2);
        pen.setColor(Qt::green);
        painter.begin(pix);
        painter.setPen(pen);
        painter.drawLine(startP,event->pos());
        painter.end();
        update();

        return;
    }

    if(isleft&&!isAtBorder)
    {
        QPoint delta=event->globalPosition().toPoint()-p;

        if((wp+delta).x()+width()>ScreenWidth||(wp+delta).y()+height()>ScreenHeight)
        {
            move(qMin(ScreenWidth-width(),qMax(0,(wp+delta).x())),qMin(ScreenHeight-height(),qMax(0,(wp+delta).y())));
            wp=pos();
            p=event->globalPosition().toPoint();
        }
        else move(qMax(0,(wp+delta).x()),qMax(0,(wp+delta).y()));
        emit moveSig();
    }
}

void CaptureRec::mouseReleaseEvent(QMouseEvent *event)
{
    if(isleft)
    {
        isleft=false;
        isAtBorder=false;
        emit releaseSig();
    }
}

void CaptureRec::enterEvent(QEnterEvent *event)
{
    if(currentChoice==CHOICE_CURSOR)
    setCursor(Qt::SizeAllCursor);
}

void CaptureRec::leaveEvent(QEvent *event)
{
    if(currentChoice==CHOICE_CURSOR)
    setCursor(Qt::ArrowCursor);
}

void CaptureRec::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(),*pix);

    // if(currentChoice==CHOICE_LINE)
    //     *pix=pix_copy.copy(pix_copy.rect());

}
