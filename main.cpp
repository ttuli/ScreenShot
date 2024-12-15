#include "widget.h"
#include "colorselectioninterface.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/new/prefix1/res/Scissors.svg"));
    //a.setQuitOnLastWindowClosed(0);
    ColorSelectionInterface w;
    w.show();
    return a.exec();
}
