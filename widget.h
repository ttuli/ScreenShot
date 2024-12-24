#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QScreen>
#include <QPixmap>
#include <QMouseEvent>
#include <QQuickWidget>
#include <QQuickItem>
#include <QKeyEvent>
#include <QSystemTrayIcon>
#include <QSettings>
#include <QFile>
#include <windows.h>
#include <windowsx.h>
#include <QMimeData>
#include <QClipboard>
#include "capturerec.h"
#include "settingdia.h"
#include "suspendwindow.h"

#define LINE 0
#define DRAW 1
#define DOWN 0
#define UP 1


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void createWindow();

    void createText();

    void setPenColor(int type,QColor color);

    void setPenWidth(int type,int width);

private:
    int ScreenWidth,ScreenHeight;

    CaptureRec *son=nullptr;
    QRect sonRect;

    SettingDia *settingdia=nullptr;

    QPoint p;

    bool isleft=false;
    bool DrawRec=false;
    bool initNotPaint=true;
    bool controlPressed=false;
    bool texting=false;

    QSystemTrayIcon *systemicon=nullptr;

    bool hasPressForOnce=false;

    QString fileSavePath;

    QQuickWidget *toolMenu=nullptr;
    QQuickWidget *lineColorMenu=nullptr;
    QQuickWidget *drawColorMenu=nullptr;

    QQuickItem *toolMenu_item=nullptr;
    QQuickItem *lineColorMenu_item=nullptr;
    QQuickItem *drawColorMenu_item=nullptr;

    //int currentChoice;
    QPoint currentP,preP;

    QList<SuspendWindow*> windowList;

protected:
    void paintEvent(QPaintEvent *event);

    void contextMenuEvent(QContextMenuEvent *event);

    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);

    bool nativeEvent(const QByteArray &eventType, void *message, qintptr *result);

private:
    void catchZoom(bool getFullScreen);

    void initAll();

    int n=0;

signals:
    void textSig();

};
#endif // WIDGET_H
