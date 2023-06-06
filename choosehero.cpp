#include "choosehero.h"
#include <QPushButton>
#include <QDebug>
#include <QMovie>
choosehero::choosehero()
{
    setWindowTitle("Bits Knight");
    QIcon icon("://resource/img/gameico.ico");
    setWindowIcon(icon);
    setFixedSize(1200, 1200);
    QPixmap bgimg("://resource/img/choosehero.png");
    QLabel *bgLabel = new QLabel(this);
    bgLabel->setPixmap(bgimg.scaled(size()));

    QPushButton *select1 = new QPushButton("Angle",this);
    select1->setGeometry(170, 920, 200, 100);
    select1->setStyleSheet("QPushButton { border: 2px solid black; border-radius: 50px; background-color: #FFFACD; }");
    QFont font("Arial", 16, QFont::Bold);
    select1->setFont(font);
    connect(select1, &QPushButton::clicked, this, [=](){startGame(0);});

    QMovie* angle = new QMovie("://resource/gif/angle_stand.gif");
    angle->setScaledSize(QSize(150, 150));
    angle->start();
    QLabel* anglelabel = new QLabel(this);
    anglelabel->setMovie(angle);
    anglelabel->setGeometry(180, 700, 200, 200); // 设置位置和大小
    anglelabel->show();

    QPushButton *select2 = new QPushButton("Elf",this);
    select2->setGeometry(510, 920, 200, 100);
    select2->setStyleSheet("QPushButton { border: 2px solid black; border-radius: 50px; background-color: #FFFACD; }");
    select2->setFont(font);
    connect(select2, &QPushButton::clicked, this, [=](){startGame(1);});

    QMovie* elf = new QMovie("://resource/gif/elf_stand.gif");
    elf->setScaledSize(QSize(150, 200));
    elf->start();
    QLabel* elflabel = new QLabel(this);
    elflabel->setMovie(elf);
    elflabel->setGeometry(520, 650, 200, 250); // 设置位置和大小
    elflabel->show();

    QPushButton *select3 = new QPushButton("Wizzard",this);
    select3->setGeometry(845, 920, 200, 100);
    select3->setStyleSheet("QPushButton { border: 2px solid black; border-radius: 50px; background-color: #FFFACD; }");
    select3->setFont(font);
    connect(select3, &QPushButton::clicked, this, [=](){startGame(2);});

    QMovie* wizzard = new QMovie("://resource/gif/wizzard_stand.gif");
    wizzard->setScaledSize(QSize(150, 200));
    wizzard->start();
    QLabel* wizzardlabel = new QLabel(this);
    wizzardlabel->setMovie(wizzard);
    wizzardlabel->setGeometry(855, 650, 200, 250); // 设置位置和大小
    wizzardlabel->show();

}

void choosehero::startGame(int hero_type)
{
    gamewindow = new GameWindow(hero_type, 0);
    gamewindow->resize(1200,1200);
    gamewindow->show();
    this->close();
}
