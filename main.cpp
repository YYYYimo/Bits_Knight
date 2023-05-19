#include "widget.h"
#include "startmenu.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartMenu w;
    w.show();

    return a.exec();
}
