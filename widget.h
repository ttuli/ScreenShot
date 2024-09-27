#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGuiApplication>
#include <QPaintEvent>
#include <QScreen>
#include <QPixmap>
#include <Qpainter>
#include <QMenu>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QSystemTrayIcon>
#include <QSettings>
#include <QFile>
#include "capturerec.h"
#include "settingdia.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    int ScreenWidth,ScreenHeight;

    QPixmap *fullScreen;

    CaptureRec *son=nullptr;

    SettingDia *settingdia=nullptr;

    QPoint p;

    bool isleft=false;

    bool DrawRec=false;

    bool initNotPaint=true;

    bool controlPressed=false;

    QSystemTrayIcon *systemicon=nullptr;

    bool hasPressForOnce=false;

    QString fileSavePath;

protected:
    void paintEvent(QPaintEvent *event);

    void contextMenuEvent(QContextMenuEvent *event);

    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);

    bool eventFilter(QObject *watched, QEvent *event);

private:
    void catchZoom(bool getFullScreen);

    void initAll();

    int n=0;
};
#endif // WIDGET_H