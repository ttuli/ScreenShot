#include "colorselectioninterface.h"

ColorSelectionInterface::ColorSelectionInterface(QWidget *parent)
    : QWidget{parent}
{
    qhb=new QHBoxLayout(this);
    qhb->setContentsMargins(5,5,5,5);
    qhb->setSpacing(0);
    size1=new QWidget(this);
    size2=new QWidget(this);
    size3=new QWidget(this);

    size1->setStyleSheet("background-color:black;border-radius:2px;");
    size1->setFixedSize(5,5);
    size2->setStyleSheet("background-color:black;border-radius:5px;");
    size2->setFixedSize(10,10);
    size3->setStyleSheet("background-color:black;border-radius:7px;border:2px solid red;");
    size3->setFixedSize(15,15);

    qhb->addWidget(size1);
    qhb->addWidget(size2);
    qhb->addWidget(size3);
}
