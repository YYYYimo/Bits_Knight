#ifndef CHOOSEHERO_H
#define CHOOSEHERO_H
#include <QWidget>
#include <QLabel>
#include <QPixmap>
class choosehero: public QWidget
{
public:
    choosehero();
    ~choosehero();
private slots:
    void startGame();
};

#endif // CHOOSEHERO_H
