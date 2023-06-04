#include "shop.h"
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMovie>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QDebug>
Shop::Shop()
{
    // 创建 QLabel 用于显示 "Shop" 字样
    QLabel *titleLabel = new QLabel("Shop", this);
    QFont font("Arial", 20, QFont::Bold);  // 设置字体为 Arial，大小为 16，加粗
    titleLabel->setFont(font);
    titleLabel->setAlignment(Qt::AlignCenter);

    // 创建三个 QLabel 用于显示 GIF 图片
    QLabel *gifLabel1 = new QLabel(this);
    QLabel *gifLabel2 = new QLabel(this);
    QLabel *gifLabel3 = new QLabel(this);

    // 加载并设置 GIF 图片
    QMovie *gifMovie1 = new QMovie("://resource/gif/shop_heart.gif", QByteArray(), this);
    QMovie *gifMovie2 = new QMovie("://resource/gif/shop_weapon.gif", QByteArray(), this);
    QMovie *gifMovie3 = new QMovie("://resource/gif/skelet_run.gif", QByteArray(), this);
    gifLabel1->setMovie(gifMovie1);
    gifLabel2->setMovie(gifMovie2);
    gifLabel3->setMovie(gifMovie3);
    gifLabel1->setFixedSize(100, 100);
    gifLabel2->setFixedSize(100, 100);
    gifLabel3->setFixedSize(100, 100);
    gifLabel1->setScaledContents(true);
    gifLabel2->setScaledContents(true);
    gifLabel3->setScaledContents(true);

    // 启动 GIF 动画
    gifMovie1->start();
    gifMovie2->start();
    gifMovie3->start();

    QLabel *textLabel1 = new QLabel("Move Speed Improved", this);
    QFont font1("Arial", 10, QFont::Bold);  // 设置字体为 Arial，大小为 16，加粗
    textLabel1->setFont(font1);
    textLabel1->setAlignment(Qt::AlignCenter);
    QLabel *textLabel2 = new QLabel("Attack Improved", this);
    textLabel2->setFont(font1);
    textLabel2->setAlignment(Qt::AlignCenter);
    QLabel *textLabel3 = new QLabel("You can have a pet!", this);
    textLabel3->setFont(font1);
    textLabel3->setAlignment(Qt::AlignCenter);

    QPushButton *button1 = new QPushButton("$10", this);
    QPushButton *button2 = new QPushButton("$20", this);
    QPushButton *button3 = new QPushButton("$50", this);


    // 创建垂直布局，将 GIF 图片和文字描述作为一组添加到布局中
    QVBoxLayout *layout0 = new QVBoxLayout;
    layout0->addWidget(titleLabel);
    layout0->setContentsMargins(10, 10, 10, 10);  // 设置外边距
    layout0->setSpacing(20);  // 设置间距
    layout0->setAlignment(Qt::AlignCenter);  // 设置对齐方式

    QVBoxLayout *layout1 = new QVBoxLayout;
    layout1->addWidget(gifLabel1);
    layout1->addWidget(textLabel1);
    layout1->addWidget(button1);
    layout1->setAlignment(gifLabel1, Qt::AlignHCenter);

    layout1->setContentsMargins(10, 10, 10, 10);  // 设置外边距
    layout1->setSpacing(20);  // 设置间距
    layout1->setAlignment(Qt::AlignCenter);  // 设置对齐方式

    QVBoxLayout *layout2 = new QVBoxLayout;
    layout2->addWidget(gifLabel2);
    layout2->addWidget(textLabel2);
    layout2->addWidget(button2);
    layout2->setAlignment(gifLabel2, Qt::AlignHCenter);

    layout2->setContentsMargins(10, 10, 10, 10);  // 设置外边距
    layout2->setSpacing(20);  // 设置间距
    layout2->setAlignment(Qt::AlignCenter);  // 设置对齐方式

    QVBoxLayout *layout3 = new QVBoxLayout;
    layout3->addWidget(gifLabel3);
    layout3->addWidget(textLabel3);
    layout3->addWidget(button3);
    layout3->setAlignment(gifLabel3, Qt::AlignHCenter);

    layout3->setContentsMargins(10, 10, 10, 10);  // 设置外边距
    layout3->setSpacing(20);  // 设置间距
    layout3->setAlignment(Qt::AlignCenter);  // 设置对齐方式

    // 创建水平布局，将三组 GIF 图片和文字描述进行水平布局
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(layout0);
    mainLayout->addLayout(layout1);
    mainLayout->addLayout(layout2);
    mainLayout->addLayout(layout3);

    setLayout(mainLayout);

    connect(button1, &QPushButton::clicked, this, &Shop::addSpeed);
    connect(button2, &QPushButton::clicked, this, &Shop::addAttack);
    connect(button3, &QPushButton::clicked, this, &Shop::havePets);

}

void Shop::savefile(QJsonObject json)
{
    QJsonDocument saveDoc(json); // 将 json 对象转换为 JSON 文档
    QByteArray saveData = saveDoc.toJson(); // 将 JSON 文档序列化为 JSON 字符串

    QFile saveFile(QStringLiteral("D:/Qt_project/night/save.json"));
    if (!saveFile.open(QIODevice::WriteOnly))
    {
        qWarning("Couldn't open the file for writing.");
    }
    else
    {
        saveFile.write(saveData); // 将 JSON 字符串写入文件
        saveFile.close();
    }
}

void Shop::addSpeed()
{
    QFile loadFile( QStringLiteral("D:/Qt_project/night/save.json"));

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
    }

    QByteArray saveData1 = loadFile.readAll();
    QJsonDocument loadDoc( QJsonDocument::fromJson(saveData1));
    QJsonObject json = loadDoc.object();
    if (json.contains("player_speed") && json["player_speed"].isDouble())
    {
        int nowspeed = json["player_speed"].toDouble();
        json.insert("player_speed", nowspeed + 2);
    }
    loadFile.close();

    savefile(json);

    StartMenu* startmenu = new StartMenu();
    startmenu->resize(1200, 1200);
    startmenu->show();

    this->close();
}

void Shop::addAttack()
{
    QFile loadFile( QStringLiteral("D:/Qt_project/night/save.json"));

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
    }

    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc( QJsonDocument::fromJson(saveData));
    QJsonObject json = loadDoc.object();
    if(json.contains("player_att") && json["player_att"].isDouble())
    {
        int nowatt = json["player_att"].toInt();
        json.insert("player_att", nowatt + 2);
    }
    loadFile.close();

    savefile(json);

    StartMenu* startmenu = new StartMenu();
    startmenu->resize(1200, 1200);
    startmenu->show();
    this->close();
}

void Shop::havePets()
{
    QFile loadFile( QStringLiteral("D:/Qt_project/night/save.json"));

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
    }

    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc( QJsonDocument::fromJson(saveData));
    QJsonObject json = loadDoc.object();
    if(json.contains("ishavepets") && json["ishavepets"].isDouble())
    {
        json.insert("ishavepets", 1);
    }
    if(json.contains("player_hp") && json["player_hp"].isDouble())
    {
        int nowhp = json["player_hp"].toInt();
        json.insert("player_hp", nowhp + 5);
    }
    loadFile.close();

    savefile(json);

    StartMenu* startmenu = new StartMenu();
    startmenu->resize(1200, 1200);
    startmenu->show();
    this->close();

}
