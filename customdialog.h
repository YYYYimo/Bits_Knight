#ifndef CUSTOMDIALOG_H
#define CUSTOMDIALOG_H
#include <QDialog>
#include <QGraphicsItem>
#include <QPixmap>
#include <QPushButton>
#include <QSharedPointer>
#include <QVBoxLayout>
#include <QMouseEvent>
#include "player.h"
class CustomDialog : public QDialog
{
    Q_OBJECT
public:
    CustomDialog(QSharedPointer<Player> item, QWidget* parent = nullptr);
private slots:
    void OnAccept();

private:
    QSharedPointer<Player> play;
    // 添加需要的控件和成员变量
    // 定义用于编辑属性的槽函数
};
#endif // CUSTOMDIALOG_H
