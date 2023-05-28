#include "choosehero.h"
choosehero::choosehero()
{

}

void choosehero::startGame()
{
    QWidget* gamew = new QWidget();
    gamew->resize(1200, 1200);
    setParent(gamew);
    gamewindow = new GameWindow(gamew);
    gamew->show();
    this->close();
}
