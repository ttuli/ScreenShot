#ifndef SUSPENDWINDOW_H
#define SUSPENDWINDOW_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>
#include <QMouseEvent>
#include <QLabel>
#include <QHBoxLayout>

class SuspendWindow : public QWidget
{
    Q_OBJECT
public:
    explicit SuspendWindow(QWidget *parent = nullptr,QPixmap pix=QPixmap());

protected:
    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);

private:
    QPoint p,wp;
    bool isleft=false;

    QLabel *label;

signals:
};

#endif // SUSPENDWINDOW_H
