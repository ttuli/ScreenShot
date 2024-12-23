#ifndef TEXTWIDGET_H
#define TEXTWIDGET_H

#include <QWidget>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QPainter>
#include <QPaintEvent>

class TextWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextWidget(QWidget *parent = nullptr);

private:
    QTextEdit *edit;
    QHBoxLayout *qhb;

protected:
    void paintEvent(QPaintEvent *event);

signals:
};

#endif // TEXTWIDGET_H
