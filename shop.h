#ifndef SHOP_H
#define SHOP_H
#include <QWidget>
#include <startmenu.h>
#include <QJsonObject>
#include <QString>
class Shop : public QWidget
{
    Q_OBJECT
public:
    explicit Shop();
    ~Shop() {}
    void savefile(QJsonObject json);
    int coins;
private slots:
    void addSpeed();
    void addAttack();
    void havePets();
};

#endif // SHOP_H
