#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QScreen>
#include <QPixmap>
#include <QMenu>
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


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void createWindow();

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

    QSystemTrayIcon *systemicon=nullptr;

    bool hasPressForOnce=false;

    QString fileSavePath;

    QQuickWidget *toolMenu=nullptr;


    QQuickItem *toolMenu_item=nullptr;

    int currentChoice;
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

};
#endif // WIDGET_H
