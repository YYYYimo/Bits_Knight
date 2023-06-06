#include "widget.h"
#include "startmenu.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartMenu w;
    QIcon icon("://resource/img/gameico.ico");
    w.setWindowIcon(icon);
    w.show();

    return a.exec();
}
