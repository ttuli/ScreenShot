#ifndef COLORSELECTIONINTERFACE_H
#define COLORSELECTIONINTERFACE_H

#include <QWidget>

class ColorSelectionInterface : public QWidget
{
    Q_OBJECT
public:
    explicit ColorSelectionInterface(QWidget *parent = nullptr);

signals:
};

#endif // COLORSELECTIONINTERFACE_H
