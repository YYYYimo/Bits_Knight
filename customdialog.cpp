#include "customdialog.h"
#include <QDebug>
CustomDialog::CustomDialog(QSharedPointer<Player> p, QWidget* parent)
    : QDialog(parent), play(p)
{
    setAttribute(Qt::WA_DeleteOnClose);
    // 创建 QLabel 控件并加载图片
    QLabel* imageLabel = new QLabel(this);
    QPixmap image("://resource/img/expbox.png");  // 替换为您的图片路径
    imageLabel->setPixmap(image);

    imageLabel->setScaledContents(true);  // 自适应大小
    imageLabel->setFixedSize(200, 200);   // 设置固定大小

    // 创建 QLabel 来显示文字
    QLabel* textLabel = new QLabel("Hello, World!", this);
    textLabel->setAlignment(Qt::AlignCenter);  // 文字居中对齐

    // 创建 QPushButton 控件
    QPushButton* closeButton = new QPushButton("Close", this);

    // 连接按钮的 clicked() 信号到槽函数，实现关闭窗口
    connect(closeButton, &QPushButton::clicked, this, &CustomDialog::OnAccept);
    // 创建布局，并将控件添加到布局中
    // 设置布局到对话框中
    QVBoxLayout* layout = new QVBoxLayout;
        layout->addWidget(imageLabel);
        layout->addWidget(closeButton);
        layout->addWidget(textLabel);

        // 设置布局到对话框中
        setLayout(layout);
    qDebug() << "gen";

        // Set the bounding rectangle for the dialog item
}

void CustomDialog::OnAccept()
{
    play->m_hp += 5;
    qDebug() << "close";
    close();
}


