#include "customdialog.h"
#include <QDebug>
CustomDialog::CustomDialog(QSharedPointer<Player> p, int ty, QWidget* parent)
    : QDialog(parent), play(p), type(ty)
{
    setAttribute(Qt::WA_DeleteOnClose);
    // 创建 QLabel 控件并加载图片
    if(type == 2)
    {
        QLabel* imageLabel1 = new QLabel(this);
        QLabel* imageLabel2 = new QLabel(this);
        QLabel* imageLabel3 = new QLabel(this);

        QPixmap image1("://resource/img/ui_heart_full.png");  // 第一张图片路径
        QPixmap image2("://resource/img/sword.png");  // 第二张图片路径
        QPixmap image3("://resource/img/speedup.png");  // 第三张图片路径

        imageLabel1->setPixmap(image1);
        imageLabel2->setPixmap(image2);
        imageLabel3->setPixmap(image3);

        imageLabel1->setFixedSize(100, 100);
        imageLabel2->setFixedSize(100, 100);
        imageLabel3->setFixedSize(100, 100);
        imageLabel1->setScaledContents(true);
        imageLabel2->setScaledContents(true);
        imageLabel3->setScaledContents(true);
        // 创建 QLabel 来显示文字
        QLabel* textLabel1 = new QLabel("Hp ++", this);
        QLabel* textLabel2 = new QLabel("Attack ++", this);
        QLabel* textLabel3 = new QLabel("Speed ++", this);

        // 创建 QPushButton 控件
        QPushButton* button1 = new QPushButton("choose it", this);
        QPushButton* button2 = new QPushButton("choose it", this);
        QPushButton* button3 = new QPushButton("choose it", this);

        connect(button1, &QPushButton::clicked, this, &CustomDialog::OnAcceptHp);
        connect(button2, &QPushButton::clicked, this, &CustomDialog::OnAcceptAtt);
        connect(button3, &QPushButton::clicked, this, &CustomDialog::OnAcceptSpeed);


        // 创建水平布局，并将控件添加到布局中
        QVBoxLayout* layout1 = new QVBoxLayout;
        layout1->addWidget(textLabel1);
        layout1->addWidget(imageLabel1);
        layout1->addWidget(button1);

        QVBoxLayout* layout2 = new QVBoxLayout;
        layout2->addWidget(textLabel2);
        layout2->addWidget(imageLabel2);
        layout2->addWidget(button2);

        QVBoxLayout* layout3 = new QVBoxLayout;
        layout3->addWidget(textLabel3);
        layout3->addWidget(imageLabel3);
        layout3->addWidget(button3);

        // 创建水平布局
        QHBoxLayout* mainLayout = new QHBoxLayout;
        mainLayout->addLayout(layout1);
        mainLayout->addSpacing(20);  // 间隔
        mainLayout->addLayout(layout2);
        mainLayout->addSpacing(20);  // 间隔
        mainLayout->addLayout(layout3);

        // 设置主布局到对话框中
        setLayout(mainLayout);
    }
    else if(type == 0)
    {
        QLabel *imageLabel = new QLabel(this);
        QPixmap imagePixmap("://resource/img/LOSE.png");  // 替换为你的图片路径
        imageLabel->setPixmap(imagePixmap);
        imageLabel->setAlignment(Qt::AlignCenter);

        // 给对话框设置标题
        setWindowTitle("LOSE GAME");

        // 改变对话框的大小以适应图片大小
        resize(imagePixmap.size());

        QPushButton *closeButton = new QPushButton("Close Game", this);
        connect(closeButton, &QPushButton::clicked, this, &CustomDialog::closeGame);

        // 创建垂直布局，并将图片控件和按钮控件添加到布局中
        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(imageLabel);
        layout->addWidget(closeButton);

        // 设置布局到对话框中
        setLayout(layout);
    }
    else if(type == 1)
    {
        QLabel *imageLabel = new QLabel(this);
        QPixmap imagePixmap("://resource/img/WIN.png");  // 替换为你的图片路径
        imageLabel->setPixmap(imagePixmap);
        imageLabel->setAlignment(Qt::AlignCenter);

        setWindowTitle("WIN GAME");

        // 创建 QPushButton 控件来关闭游戏
        QPushButton *closeButton = new QPushButton("Close Game", this);
        connect(closeButton, &QPushButton::clicked, this, &CustomDialog::closeGame);

        // 创建垂直布局，并将控件添加到布局中
        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(imageLabel);
        layout->addWidget(closeButton);

        // 设置布局到对话框中
        setLayout(layout);
    }

}

void CustomDialog::OnAcceptHp()
{
    play->setHP(5);
    close();
}

void CustomDialog::OnAcceptAtt()
{
    play->setAttack(2);
    close();
}

void CustomDialog::OnAcceptSpeed()
{
    play->setSpeed(2);
    close();
}

void CustomDialog::closeGame()
{
    close();
}


