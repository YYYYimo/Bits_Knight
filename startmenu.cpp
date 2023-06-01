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
    QPixmap bgimg("://resource/img/startpage.jpg");
    QLabel *bgLabel = new QLabel(this);
    bgLabel->setPixmap(bgimg.scaled(size()));

    QPushButton *startbutton = new QPushButton("start",this);
    startbutton->setGeometry(500, 600, 200, 100);
    startbutton->setStyleSheet("QPushButton { border: 2px solid black; border-radius: 50px; background-color: #FFFACD; }");
    QFont font("Arial", 16, QFont::Bold);
    startbutton->setFont(font);
    connect(startbutton, SIGNAL(clicked()), this, SLOT(chooseWindow()));

    QPushButton *shopbutton = new QPushButton("shop",this);
    shopbutton->setGeometry(500, 710, 200, 100);
    shopbutton->setStyleSheet("QPushButton { border: 2px solid black; border-radius: 50px; background-color: #FFFACD; }");
    shopbutton->setFont(font);
    connect(shopbutton, SIGNAL(clicked()), this, SLOT(shopWindow()));

    QPushButton *archibutton = new QPushButton("archives",this);
    archibutton->setGeometry(500, 820, 200, 100);
    archibutton->setStyleSheet("QPushButton { border: 2px solid black; border-radius: 50px; background-color: #FFFACD; }");
    archibutton->setFont(font);
    //connect(archibutton, SIGNAL(clicked()), this, SLOT(startGame()));

    QPushButton *readbutton = new QPushButton("read",this);
    readbutton->setGeometry(500, 930, 200, 100);
    readbutton->setStyleSheet("QPushButton { border: 2px solid black; border-radius: 50px; background-color: #FFFACD; }");
    readbutton->setFont(font);
    //connect(readbutton, SIGNAL(clicked()), this, SLOT(startGame()));

}

void StartMenu::chooseWindow()
{
    QWidget* choosew = new QWidget();
    choosew->resize(1200, 1200);
    setParent(choosew);
    choose = new choosehero(choosew);
    choosew->show();
    this->close();
}

void StartMenu::shopWindow()
{
    QWidget* shopw = new QWidget();
    shopw->resize(1200, 1200);
    setParent(shopw);
    shop = new Shop(shopw);
    shopw->show();
    this->close();
}

StartMenu::~StartMenu()
{

}

#endif // STARTMENU_CPP
