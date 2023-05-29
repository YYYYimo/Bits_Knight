#ifndef STARTMENU_H
#define STARTMENU_H

#include <QWidget>
#include "choosehero.h"
#include "gamewindow.h"
class StartMenu: public QWidget
{
    Q_OBJECT
public:
    explicit StartMenu(QWidget *parent = nullptr);
    ~StartMenu();
private slots:
    void chooseWindow();
private:
    GameWindow* gamewindow;
    choosehero* choose;
};


#endif // STARTMENU_H
