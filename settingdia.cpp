#include "settingdia.h"
#include <QHBoxLayout>

SettingDia::SettingDia(QWidget *parent,QString savePos)
    : QDialog{parent}
{
    fileSavePosition=savePos;
    setWindowFlag(Qt::WindowStaysOnTopHint);

    QHBoxLayout *qhb=new QHBoxLayout(this);
    setMinimumSize(500,400);


    qwid=new QQuickWidget(this);
    qwid->setSource(QUrl("qrc:/SettingDialog.qml"));
    qwid->setResizeMode(QQuickWidget::SizeRootObjectToView);
    rootobject=(QObject*)(qwid->rootObject());

    qhb->addWidget(qwid);
    qhb->setContentsMargins(0,0,0,0);
    connect(rootobject,SIGNAL(changeSavePath()),this,SLOT(ChangeSavePath()));

    QMetaObject::invokeMethod(rootobject,"initSetting",Q_ARG(QVariant,savePos));
}


void SettingDia::ChangeSavePath()
{
    QString path=QFileDialog::getSaveFileName(this,"保存位置","未命名.png");
    if(path.isEmpty())return;
    path.remove(path.lastIndexOf("/"),100);
    QMetaObject::invokeMethod(rootobject,"initSetting",Q_ARG(QVariant,path));
    emit pathChange(path);
}
