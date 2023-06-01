#ifndef STARTMENU_H
#define STARTMENU_H

#include <QWidget>
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
private:
    GameWindow* gamewindow;
    choosehero* choose;
    Shop* shop;
};


#endif // STARTMENU_H
