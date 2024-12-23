#include "suspendwindow.h"

SuspendWindow::SuspendWindow(QWidget *parent, QPixmap pix,QString SavePath)
    : QWidget{parent}
{
    setWindowFlags(Qt::FramelessWindowHint|Qt::SubWindow|Qt::WindowStaysOnTopHint);
    QGraphicsDropShadowEffect *gra=new QGraphicsDropShadowEffect;
    gra->setColor(Qt::green);
    gra->setOffset(0,0);
    gra->setBlurRadius(35);

    scaleProportion=QGuiApplication::primaryScreen()->devicePixelRatio();

    m_width=pix.width()/scaleProportion;
    m_height=pix.height()/scaleProportion;

    setMaximumSize(m_width*3,m_height*3);
    setMinimumSize(m_width/5,m_height/5);
    resize(m_width+6,m_height+6);

    label=new QLabel(this);
    label->setPixmap(pix);
    label->setScaledContents(1);
    label->setAttribute(Qt::WA_TransparentForMouseEvents);

    QHBoxLayout *qhb=new QHBoxLayout(this);
    qhb->setContentsMargins(3,3,3,3);
    qhb->addWidget(label);

    label->setGraphicsEffect(gra);

    menu=new QMenu(this);

    QAction *action1=new QAction("关闭");
    QAction *action2=new QAction("保存");
    QAction *action3=new QAction("另存为");

    connect(action1,&QAction::triggered,this,&SuspendWindow::close);
    connect(action2,&QAction::triggered,[=]{
        QString filename;
        QString currentDate=QDate::currentDate().toString().replace(" ","_");
        if(currentUsedFileName.isEmpty())
        {
            filename=currentDate+"1";
            while(QFile::exists(savaPath+"/"+filename+".png"))
            {
                num++;
                filename=currentDate+QString::number(num);
                currentUsedFileName=currentDate+QString::number(num+1);
            }
            filename+=".png";
            filename=savaPath+"/"+filename;
            currentUsedFileName+=".png";
            currentUsedFileName=savaPath+"/"+currentUsedFileName;
        }
        else
        {
            filename=currentUsedFileName;
            num++;
            currentUsedFileName=currentDate+QString::number(num+1);
            currentUsedFileName+=".png";
            currentUsedFileName=savaPath+"/"+currentUsedFileName;
        }
        m_pix.save(filename);
    });
    connect(action3,&QAction::triggered,[=]{
        QString path=QFileDialog::getSaveFileName(this,"保存位置","未命名.png");
        if(path.isEmpty())return;
        path.remove(path.lastIndexOf("/"),100);
        QString filename;
        QString currentDate=QDate::currentDate().toString().replace(" ","_");
        if(currentUsedFileName.isEmpty())
        {
            filename=currentDate+"1";
            while(QFile::exists(path+"/"+filename+".png"))
            {
                num++;
                filename=currentDate+QString::number(num);
                currentUsedFileName=currentDate+QString::number(num+1);
            }
            filename+=".png";
            filename=path+"/"+filename;
            currentUsedFileName+=".png";
            currentUsedFileName=path+"/"+currentUsedFileName;
        }
        else
        {
            filename=currentUsedFileName;
            num++;
            currentUsedFileName=currentDate+QString::number(num+1);
            currentUsedFileName+=".png";
            currentUsedFileName=path+"/"+currentUsedFileName;
        }
        m_pix.save(filename);
    });

    menu->addAction(action1);
    menu->addAction(action2);
    menu->addAction(action3);

    savaPath=SavePath;
    m_pix=pix;
    currentUsedFileName="";

    setMouseTracking(1);
}

void SuspendWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        isleft=true;
        wp=pos();
        p=event->globalPosition().toPoint();
        initWidth=width();
        initHeight=height();
    }
}

void SuspendWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(isleft)
    {
        QPoint point=event->globalPosition().toPoint()-p;
        if(isborder)
        {
            resize(initWidth+point.x(),initHeight+point.x()*initHeight/initWidth);
        }
        else
        move(wp+point);
        return;
    }

    if(event->pos().x()>width()-10&&event->pos().y()>height()-10)
    {
        setCursor(Qt::SizeFDiagCursor);
        isborder=true;
    }
    else
    {
        setCursor(Qt::ArrowCursor);
        isborder=false;
    }
}

void SuspendWindow::mouseReleaseEvent(QMouseEvent *event)
{
    isleft=false;
}

void SuspendWindow::contextMenuEvent(QContextMenuEvent *event)
{
    menu->exec(event->globalPos());
}

void SuspendWindow::leaveEvent(QEvent *event)
{
    setCursor(Qt::ArrowCursor);
}
