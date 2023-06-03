#include "playerwizzard.h"
#include <QMovie>
playerwizzard::playerwizzard()
{
    m_type = 2;
    m_hp = 10;
    m_attack = 1;
    width = 70;
    height = 110;
    m_x = 0;
    m_y = 0;
    m_speed = 1;

    QString imgpath = "://resource/gif/wizzard_run.gif";
    m_movie = new QMovie(imgpath);
    m_movie->start();
}
