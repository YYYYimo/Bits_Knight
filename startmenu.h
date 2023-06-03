#ifndef STARTMENU_H
#define STARTMENU_H

#include <QWidget>
#include <QGraphicsProxyWidget>
#include <QGraphicsLinearLayout>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include "choosehero.h"
#include "gamewindow.h"
#include "shop.h"
class StartMenu: public QWidget
{
    Q_OBJECT
public:
    explicit StartMenu(QWidget *parent = nullptr);
    ~StartMenu();
private slots:
    void chooseWindow();
    void shopWindow();
    void continueGame();
private:
    GameWindow* gamewindow;
    choosehero* choose;
    Shop* shop;
};


#endif // STARTMENU_H
