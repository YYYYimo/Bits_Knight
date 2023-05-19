#ifndef STARTMENU_H
#define STARTMENU_H

#include <QWidget>
#include "gamewindow.h"
class StartMenu: public QWidget
{
    Q_OBJECT
public:
    explicit StartMenu(QWidget *parent = nullptr);
    ~StartMenu();
private slots:
    void startGame();
private:
    GameWindow* gamewindow;
};


#endif // STARTMENU_H
