#ifndef CAPTUREREC_H
#define CAPTUREREC_H

#include <QWidget>
#include <QMouseEvent>

class CaptureRec : public QWidget
{
    Q_OBJECT
public:
    explicit CaptureRec(QWidget *parent = nullptr,int ScreenW=0,int ScreenH=0);

protected:
    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);

    void enterEvent(QEnterEvent *event);

    void leaveEvent(QEvent *event);

private:
    bool isleft=false;

    QPoint p,wp;

    bool isAtBorder=false;

    int ScreenWidth,ScreenHeight;

signals:
    void moveSig();
};

#endif // CAPTUREREC_H
