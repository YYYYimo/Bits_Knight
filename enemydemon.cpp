#include "enemydemon.h"
#include <QDebug>
enemydemon::enemydemon(QSharedPointer<Player> pl)
{
    m_type = 0;
    m_hp = 10;
    fullHp = 10;
    m_attack = 1;
    width = 70;
    height = 70;
    m_x = 0;
    m_y = 0;
    m_speed = 1;
    play = pl;

    QString imgpath = "://resource/gif/small_demon_run.gif";
    m_movie = new QMovie(imgpath);
    m_movie->start();
}


