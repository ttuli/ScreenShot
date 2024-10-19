#include "widget.h"
#include <QDate>
#include <QDateTime>
#include <QApplication>
#include <QDir>
#include <QKeyEvent>
#include <QFileInfo>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    ScreenWidth=QGuiApplication::primaryScreen()->size().width();
    ScreenHeight=QGuiApplication::primaryScreen()->size().height();

    setWindowFlags(Qt::FramelessWindowHint|Qt::SubWindow|Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_StyledBackground);

    initNotPaint=true;

    initAll();

    HWND hwnd=(HWND)this->winId();
    RegisterHotKey(hwnd,1,MOD_ALT,0x43);
}

Widget::~Widget()
{

}


void Widget::paintEvent(QPaintEvent *event)
{
    if(initNotPaint)return;
    QPainter painter(this);
    painter.fillRect(0,0,width(),height(),QColor(0,0,0,100));
    if(DrawRec)
    {
        DrawRec=false;
        painter.save();
        painter.setBrush(QColor(0,0,0,5));
        painter.setPen(Qt::transparent);
        painter.setCompositionMode(QPainter::CompositionMode_SourceOut);
        painter.drawRect(son->geometry());
        painter.restore();
    }
}

void Widget::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu *menu=new QMenu(this);
    QAction *action1=new QAction("截取选中部分");
    QAction *action2=new QAction("截取全屏");
    QAction *action3=new QAction("取消选区");
    QAction *action4=new QAction("退出截图");
    menu->addAction(action1);
    menu->addAction(action2);
    menu->addAction(action3);
    menu->addAction(action4);

    connect(action1,&QAction::triggered,[=]{
        catchZoom(false);
    });

    connect(action2,&QAction::triggered,[=]{
        catchZoom(true);
    });

    connect(action3,&QAction::triggered,[=]{
        DrawRec=false;
        if(son!=nullptr)
        son->deleteLater();
        son=nullptr;
        update();
    });

    connect(action4,&QAction::triggered,[=]{
        if(son!=nullptr)
        son->deleteLater();
        son=nullptr;
        hide();
    });

    menu->exec(event->globalPos());
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        isleft=true;
        p=event->globalPosition().toPoint();
        if(son)
        {
            son->deleteLater();
            son=nullptr;
        }
        son=new CaptureRec(this,ScreenWidth,ScreenHeight);
        son->setVisible(1);
        son->move(p);
        connect(son,&CaptureRec::moveSig,[=]{
            DrawRec=true;
            update();
        });
        DrawRec=false;
        update();
    }
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if(isleft)
    {
        QPoint CurrentPos=event->globalPosition().toPoint();
        son->resize(qAbs(CurrentPos.x()-p.x()),qAbs(CurrentPos.y()-p.y()));
        if(CurrentPos.x()<p.x()&&CurrentPos.y()>p.y())
        {
            son->move(CurrentPos.x(),p.y());
        }
        else if(CurrentPos.x()>p.x()&&CurrentPos.y()<p.y())
        {
            son->move(p.x(),CurrentPos.y());
        }
        else if(CurrentPos.x()<p.x()&&CurrentPos.y()<p.y())
        {
            son->move(CurrentPos);
        }
        DrawRec=true;
        update();
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    isleft=false;
}

bool Widget::nativeEvent(const QByteArray &eventType, void *message, qintptr *result)
{
    if (eventType == "windows_generic_MSG")
    {
        MSG* msg = static_cast<MSG*>(message);
        if (msg->message == WM_HOTKEY)
        {
            int hotkeyId = msg->wParam;
            if (hotkeyId == 1)
            {
                systemicon->activated(QSystemTrayIcon::Trigger);
            }
            return true;  // 事件已处理
        }
    }
    return false;
}


void Widget::catchZoom(bool getFullScreen)
{
    QString currentDate=QDate::currentDate().toString().replace(" ","_");
    int num=1;
    QString filename=currentDate+"1";
    while(QFile::exists(filename+".png"))
    {
        num++;
        filename=currentDate+QString::number(num);
    }
    filename+=".png";
    filename=fileSavePath+"/"+filename;;
    if(!getFullScreen)
    {
        QPixmap pix=QApplication::primaryScreen()->grabWindow(0,son->x(),son->y(),son->width(),son->height());
        pix.save(filename,"png");
        QGuiApplication::clipboard()->setPixmap(pix);
    }
    else
    {
        hide();
        QPixmap pix=QApplication::primaryScreen()->grabWindow();
        pix.save(filename,"png");
        QGuiApplication::clipboard()->setPixmap(pix);
    }
    hide();
}

void Widget::initAll()
{
    QMenu *systemMenu=new QMenu(this);
    QAction *action1=new QAction("截图");
    QAction *action2=new QAction("设置");
    QAction *action3=new QAction("彻底退出");

    connect(action2,&QAction::triggered,[=]{
        if(settingdia!=nullptr)
        {
            settingdia->deleteLater();
        }
        settingdia=new SettingDia(this,fileSavePath);
        connect(settingdia,&SettingDia::pathChange,[=](QString path){
            QSettings setting("initialFile.ini");
            setting.setValue("path",path);
            fileSavePath=path;
        });
        settingdia->exec();
        settingdia->raise();
    });

    connect(action3,&QAction::triggered,[=]{
        QApplication::quit();
    });
    systemMenu->addAction(action1);
    systemMenu->addAction(action2);
    systemMenu->addAction(action3);
    systemicon=new QSystemTrayIcon(this);
    systemicon->setContextMenu(systemMenu);
    systemicon->setIcon(QIcon(":/new/prefix1/res/Scissors.svg"));
    systemicon->show();
    systemicon->setToolTip("截图工具");
    connect(action1,&QAction::triggered,[=]{
        systemicon->activated(QSystemTrayIcon::Trigger);
    });
    connect(systemicon,&QSystemTrayIcon::activated,[=](QSystemTrayIcon::ActivationReason reson){
        if(reson!=QSystemTrayIcon::Trigger)return;
        DrawRec=false;
        if(son!=nullptr)
            son->deleteLater();
        son=nullptr;
        initNotPaint=false;
        showFullScreen();
    });

    QFile file("initialFile.ini");
    file.open(QIODevice::Append);
    file.close();
    QSettings setting("initialFile.ini");
    fileSavePath=setting.value("path").toString();

}
