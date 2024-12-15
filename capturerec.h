#ifndef CAPTUREREC_H
#define CAPTUREREC_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QGuiApplication>
#include <Qpainter>
#include <QPaintEvent>

#define CHOICE_CURSOR 0
#define CHOICE_LINE CHOICE_CURSOR+1
#define CHOICE_DRAW CHOICE_CURSOR+2

class CaptureRec : public QWidget
{
    Q_OBJECT
public:
    explicit CaptureRec(QWidget *parent = nullptr,int ScreenW=0,int ScreenH=0);

    int currentChoice;

public slots:
    void setCurrentChoice(int choice);

    int getCurrentChoice();

protected:
    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);

    void enterEvent(QEnterEvent *event);

    void leaveEvent(QEvent *event);

    void paintEvent(QPaintEvent*);

private:
    bool isleft=false;
    bool hasDraw=false;

    QPoint p,wp;//用于窗口移动

    QPoint preP,currentP;//用于画各种不规则线

    QPoint startP;

    bool isAtBorder=false;

    int ScreenWidth,ScreenHeight;

    QLabel *label;
    QHBoxLayout *qhb;
    QPixmap currentPix;
    QPixmap *pix;
    QPixmap pix_copy;

signals:
    void moveSig();

    void releaseSig();

    void updateSig();
};

#endif // CAPTUREREC_H
