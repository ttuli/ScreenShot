#include "textwidget.h"

TextWidget::TextWidget(QWidget *parent)
    : QWidget{parent}
{
    edit=new QTextEdit(this);
    edit->setAttribute(Qt::WA_TranslucentBackground);
    qhb=new QHBoxLayout(this);

    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlag(Qt::FramelessWindowHint);
    setFixedSize(150,40);
    QFont font;
    font.setPixelSize(30);
    edit->setFont(font);
}

void TextWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(5);
    painter.setPen(pen);
    painter.setBrush(Qt::transparent);
    painter.drawRect(0,0,width(),height());
}

