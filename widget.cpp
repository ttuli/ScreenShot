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

    currentChoice=0;

    initAll();

    HWND hwnd=(HWND)this->winId();
    RegisterHotKey(hwnd,1,MOD_ALT,0x43);
}

Widget::~Widget()
{
    for(int i=0;i<windowList.size();i++)
    {
        if(windowList.at(i)!=nullptr)
        windowList.at(i)->deleteLater();
    }
    windowList.clear();
}

void Widget::createWindow()
{
    SuspendWindow *w=new SuspendWindow(0,QApplication::primaryScreen()->grabWindow(0,son->x(),son->y(),son->width(),son->height()),fileSavePath);
    w->move(son->x()-3,son->y()-3);
    w->show();
    windowList<<w;

    if(son!=nullptr)
        son->deleteLater();
    son=nullptr;
    toolMenu->hide();
    lineColorMenu->hide();
    drawColorMenu->hide();
    hide();
}

void Widget::createText()
{
    texting=true;
}

void Widget::setPenColor(int type, QColor color)
{
    if(type==LINE)
    {
        currentLineColor=color;
    }
    else if(type==DRAW)
    {
        currentDrawColor=color;
    }
}

void Widget::setPenWidth(int type, int width)
{
    width*=2;
    if(type==LINE)
    {
        currentLineWidth=width;
    }
    else if(type==DRAW)
    {
        currentDrawWidth=width;
    }
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
        son->deleteLater();
        son=nullptr;
        toolMenu->hide();
        QMetaObject::invokeMethod(toolMenu_item,"initCurrentState");
        update();
    });

    connect(action4,&QAction::triggered,[=]{
        if(son!=nullptr)
        son->deleteLater();
        son=nullptr;
        toolMenu->hide();
        hide();
    });

    menu->exec(event->globalPos());
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        if(son!=nullptr)
        {
            if(currentChoice!=CHOICE_CURSOR)
            {
                return;
            }
            son->deleteLater();
            son=nullptr;
        }

        isleft=true;
        p=event->globalPosition().toPoint();
        toolMenu->hide();
        lineColorMenu->hide();
        drawColorMenu->hide();

        QMetaObject::invokeMethod(toolMenu_item,"initCurrentState");

        son=new CaptureRec(this,ScreenWidth,ScreenHeight);
        son->setVisible(1);
        son->resize(0,0);
        son->move(p);
        connect(son,&CaptureRec::moveSig,[=]{
            toolMenu->hide();
            lineColorMenu->hide();
            drawColorMenu->hide();
            DrawRec=true;
            update();
        });
        connect(son,&CaptureRec::releaseSig,[=]{
            if(son->y()+son->height()+5+toolMenu->height()<ScreenHeight)
                toolMenu->move(son->x(),son->y()+son->height()+5);
            else if(son->y()-5-toolMenu->height()>0)
            {
                toolMenu->move(son->x(),son->y()-toolMenu->height()-5);
            }
            else
            {
                toolMenu->move(son->x(),son->y()+son->height()-5-toolMenu->height());
            }
            toolMenu->show();
        });
        connect(son,&CaptureRec::updateSig,[=]{
            DrawRec=true;
            update();
        });
        connect(son,&CaptureRec::colorInterfaceSig,[=]{
            if(currentChoice==CHOICE_CURSOR)
            {
                lineColorMenu->hide();
                drawColorMenu->hide();
            }
            else if(currentChoice==CHOICE_LINE)
            {
                lineColorMenu->show();
                drawColorMenu->hide();
                lineColorMenu->move(toolMenu->x()-28,toolMenu->y()+toolMenu->height());
            }
            else if(currentChoice==CHOICE_DRAW)
            {
                lineColorMenu->hide();
                drawColorMenu->show();
                drawColorMenu->move(toolMenu->x()-63,toolMenu->y()+toolMenu->height());
            }
        });
        connect(toolMenu_item,SIGNAL(choiceSig(int)),son,SLOT(setCurrentChoice(int)));

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
        sonRect=son->geometry();
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
    if(!isleft)return;
    isleft=false;
    if(son->y()+son->height()+5+toolMenu->height()<ScreenHeight)
        toolMenu->move(son->x(),son->y()+son->height()+5);
    else if(son->y()-5-toolMenu->height()>0)
    {
        toolMenu->move(son->x(),son->y()-toolMenu->height()-5);
    }
    else
    {
        toolMenu->move(son->x(),son->y()+son->height()-5-toolMenu->height());
    }
    toolMenu->show();

    toolMenu->raise();
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
    if(son==nullptr||son->isHidden()||son->width()<=5)return;
    QString currentDate=QDate::currentDate().toString().replace(" ","_");
    int num=1;
    QString filename=currentDate+"1";

    while(QFile::exists(fileSavePath+"/"+filename+".png"))
    {
        num++;
        filename=currentDate+QString::number(num);
    }
    filename+=".png";
    filename=fileSavePath+"/"+filename;

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
    currentDrawColor=QColor(Qt::red);
    currentLineColor=QColor(Qt::red);
    currentDrawWidth=2;
    currentLineWidth=2;

    toolMenu=new QQuickWidget(this);
    toolMenu->setClearColor(Qt::transparent);
    toolMenu->setAttribute(Qt::WA_AlwaysStackOnTop);
    toolMenu->setResizeMode(QQuickWidget::SizeViewToRootObject);
    toolMenu->setSource(QUrl("qrc:/ToolMenu.qml"));
    toolMenu->hide();
    toolMenu_item=toolMenu->rootObject();

    connect(toolMenu_item,SIGNAL(pinSig()),this,SLOT(createWindow()));

    lineColorMenu=new QQuickWidget(this);
    lineColorMenu->setClearColor(Qt::transparent);
    lineColorMenu->setAttribute(Qt::WA_AlwaysStackOnTop);
    lineColorMenu->setResizeMode(QQuickWidget::SizeViewToRootObject);
    lineColorMenu->setSource(QUrl("qrc:/ColorSelectionInterface.qml"));
    lineColorMenu->hide();
    lineColorMenu_item=lineColorMenu->rootObject();
    QMetaObject::invokeMethod(lineColorMenu_item,"setType",Q_ARG(QVariant,LINE));

    connect(lineColorMenu_item,SIGNAL(colorSig(int,QColor)),this,SLOT(setPenColor(int,QColor)));
    connect(lineColorMenu_item,SIGNAL(widthSig(int,int)),this,SLOT(setPenWidth(int,int)));

    drawColorMenu=new QQuickWidget(this);
    drawColorMenu->setClearColor(Qt::transparent);
    drawColorMenu->setAttribute(Qt::WA_AlwaysStackOnTop);
    drawColorMenu->setResizeMode(QQuickWidget::SizeViewToRootObject);
    drawColorMenu->setSource(QUrl("qrc:/ColorSelectionInterface.qml"));
    drawColorMenu->hide();
    drawColorMenu_item=drawColorMenu->rootObject();
    QMetaObject::invokeMethod(drawColorMenu_item,"setType",Q_ARG(QVariant,DRAW));

    connect(drawColorMenu_item,SIGNAL(colorSig(int,QColor)),this,SLOT(setPenColor(int,QColor)));
    connect(drawColorMenu_item,SIGNAL(widthSig(int,int)),this,SLOT(setPenWidth(int,int)));

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

