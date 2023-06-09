#ifndef STARTMENU_CPP
#define STARTMENU_CPP

#include "startmenu.h"
#include <QPushButton>
#include <QPixmap>
#include <QLabel>
#include <QMainWindow>

StartMenu::StartMenu(QWidget *parent):QWidget(parent)
{
    setWindowTitle("Bits Knight");
    setFixedSize(1200, 1200);
    QPixmap bgimg("://resource/img/startpage.jpg");
    QLabel *bgLabel = new QLabel(this);
    bgLabel->setPixmap(bgimg.scaled(size()));

    QPushButton *startbutton = new QPushButton("Start",this);
    startbutton->setGeometry(500, 600, 200, 100);
    startbutton->setStyleSheet("QPushButton { border: 2px solid black; border-radius: 50px; background-color: #FFFACD; }");
    QFont font("Arial", 16, QFont::Bold);
    startbutton->setFont(font);
    connect(startbutton, SIGNAL(clicked()), this, SLOT(chooseWindow()));

    QPushButton *shopbutton = new QPushButton("Shop",this);
    shopbutton->setGeometry(500, 710, 200, 100);
    shopbutton->setStyleSheet("QPushButton { border: 2px solid black; border-radius: 50px; background-color: #FFFACD; }");
    shopbutton->setFont(font);
    connect(shopbutton, SIGNAL(clicked()), this, SLOT(shopWindow()));

    QPushButton *archibutton = new QPushButton("Continue",this);
    archibutton->setGeometry(500, 820, 200, 100);
    archibutton->setStyleSheet("QPushButton { border: 2px solid black; border-radius: 50px; background-color: #FFFACD; }");
    archibutton->setFont(font);
    connect(archibutton, SIGNAL(clicked()), this, SLOT(continueGame()));

    QPushButton *readbutton = new QPushButton("read",this);
    readbutton->setGeometry(500, 930, 200, 100);
    readbutton->setStyleSheet("QPushButton { border: 2px solid black; border-radius: 50px; background-color: #FFFACD; }");
    readbutton->setFont(font);
    //connect(readbutton, SIGNAL(clicked()), this, SLOT(startGame()));

}

void StartMenu::chooseWindow()
{
    choose = new choosehero();
    choose->resize(1200, 1200);
    choose->show();
    this->close();
}

void StartMenu::shopWindow()
{
    shop = new Shop();
    shop->resize(800, 280);
    shop->show();
    this->close();
}

void StartMenu::continueGame()
{
    QFile loadFile( QStringLiteral("D:/Qt_project/night/save.json"));

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
    }
    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc( QJsonDocument::fromJson(saveData));
    QJsonObject json = loadDoc.object();
    int player_type;
    if(json.contains("player_type") && json["player_type"].isDouble())
        player_type = json["player_type"].toInt();


    gamewindow = new GameWindow(player_type, 1);
    gamewindow->resize(1200, 1200);
    gamewindow->show();
    this->close();
}

StartMenu::~StartMenu()
{

}

#endif // STARTMENU_CPP
