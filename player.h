#ifndef PLAYER_H
#define PLAYER_H
#include <QObject>
#include <QGraphicsItem>

class Player : public QGraphicsObject
{
    Q_OBJECT
public:
    Player();

    QRectF boundingRect() const override;
    bool collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const override;
    int type() const override;

    void setMovie(const QString& path);
    void setSpeed(qreal speed);
    void setPos(qreal x, qreal y);
    void setHP(int hp);
    void setAttack(int attack);
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent *event);

    void advance();

    int m_type;
    int m_hp;
    int m_attack;
    int width;
    int height;
    qreal m_x;
    qreal m_y;
    qreal m_speed;
    QMovie* m_movie;
    QTimer* keyRespondTimer;
    QList<int> keys;
private slots:
    void slotTimeOut();
protected:
    QRectF boundingRect();
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
};


#endif // PLAYER_H
