#ifndef COLORSELECTIONINTERFACE_H
#define COLORSELECTIONINTERFACE_H

#include <QWidget>
#include <QHBoxLayout>

class ColorSelectionInterface : public QWidget
{
    Q_OBJECT
public:
    explicit ColorSelectionInterface(QWidget *parent = nullptr);


private:
    QHBoxLayout *qhb;

    QWidget *size1;
    QWidget *size2;
    QWidget *size3;

signals:
};

#endif // COLORSELECTIONINTERFACE_H
