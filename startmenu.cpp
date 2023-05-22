#ifndef STARTMENU_CPP
#define STARTMENU_CPP

#include "startmenu.h"
#include <QPushButton>
#include <QPixmap>
#include <QLabel>
#include <QMainWindow>

StartMenu::StartMenu(QWidget *parent):QWidget(parent)
{
    setFixedSize(1200, 1200);
    QPixmap bgimg("://resource/img/startpage.png");
    QLabel *bgLabel = new QLabel(this);
    bgLabel->setPixmap(bgimg.scaled(size()));

    QPushButton *startbutton = new QPushButton("start",this);
    //startbutton->setStyleSheet("QPushButton{border-image: url(:/img/background/resource/button.jpg)}");
    startbutton->setGeometry(200, 400, 400, 100);

    connect(startbutton, SIGNAL(clicked()), this, SLOT(startGame()));

}

void StartMenu::startGame()
{
    QWidget* gamew = new QWidget();
    gamew->resize(1500, 1200);
    setParent(gamew);
    gamewindow = new GameWindow(gamew);
    gamew->show();
    this->close();
}

StartMenu::~StartMenu()
{

}

#endif // STARTMENU_CPP
