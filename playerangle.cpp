#include "playerangle.h"
#include <QMovie>
playerAngle::playerAngle()
{
    m_type = 0;
    m_hp = 100;
    m_attack = 10;
    width = 100;
    height = 100;
    m_x = 0;
    m_y = 0;
    m_speed = 5;

    QString imgpath = ":/res/resource/gif/angle.gif";
    m_movie = new QMovie(imgpath);
    m_movie->start();
}
