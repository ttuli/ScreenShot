#ifndef SETTINGDIA_H
#define SETTINGDIA_H

#include <QDialog>
#include <QQuickWidget>
#include <QFileDialog>

class SettingDia : public QDialog
{
    Q_OBJECT
public:
    explicit SettingDia(QWidget *parent = nullptr,QString savePos="");

    static SettingDia *getInstance(QString savePos);

private:
    QQuickWidget *qwid;

    QObject *rootobject=nullptr;

    QString fileSavePosition;

private slots:
    void ChangeSavePath();

signals:
    void pathChange(QString path);
};

#endif // SETTINGDIA_H
