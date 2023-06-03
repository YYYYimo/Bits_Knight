#ifndef CUSTOMDIALOG_H
#define CUSTOMDIALOG_H
#include <QDialog>
#include <QGraphicsItem>
#include <QPixmap>
#include <QPushButton>
#include <QSharedPointer>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMouseEvent>
#include "player.h"
class CustomDialog : public QDialog
{
    Q_OBJECT
public:
    CustomDialog(QSharedPointer<Player> item, int type, QWidget* parent = nullptr);
private slots:
    void OnAcceptHp();
    void OnAcceptAtt();
    void OnAcceptSpeed();

private:
    QSharedPointer<Player> play;
    int type;
};
#endif // CUSTOMDIALOG_H
