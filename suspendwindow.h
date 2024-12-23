#ifndef SUSPENDWINDOW_H
#define SUSPENDWINDOW_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>
#include <QMouseEvent>
#include <QLabel>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMenu>
#include <QScreen>

class SuspendWindow : public QWidget
{
    Q_OBJECT
public:
    explicit SuspendWindow(QWidget *parent = nullptr,QPixmap pix=QPixmap(),QString SavePath="");

protected:
    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);

    void contextMenuEvent(QContextMenuEvent *event);

    void leaveEvent(QEvent *event);

private:
    QPoint p,wp;
    bool isleft=false;
    bool isborder=false;
    int initWidth;
    int initHeight;

    QLabel *label;
    QMenu *menu=nullptr;

    QPixmap m_pix;
    QString currentUsedFileName;
    int num=1;

    qreal scaleProportion;
    int m_width,m_height;
public:
    QString savaPath;

signals:
};

#endif // SUSPENDWINDOW_H
