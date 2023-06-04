#ifndef CHOOSEHERO_H
#define CHOOSEHERO_H
#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include "gamewindow.h"
class choosehero: public QWidget
{
    Q_OBJECT
public:
    choosehero();
    ~choosehero(){}
    void startGame(int hero_type);
private:
    GameWindow* gamewindow;
};

#endif // CHOOSEHERO_H
