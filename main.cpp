#include "widget.h"
#include "settingdia.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/new/prefix1/res/Scissors.svg"));
    a.setQuitOnLastWindowClosed(0);
    Widget w;
    return a.exec();
}
