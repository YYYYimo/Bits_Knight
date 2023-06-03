#ifndef SHOP_H
#define SHOP_H
#include <QWidget>
class Shop : public QWidget
{
    Q_OBJECT
public:
    explicit Shop(QWidget *parent = nullptr);
    ~Shop() {}
private slots:
    void addSpeed();
    void addAttack();
    void havePets();
};

#endif // SHOP_H
