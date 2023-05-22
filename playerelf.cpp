#include "playerelf.h"

playerelf::playerelf()
{
    m_type = 0;
    m_hp = 10;
    m_attack = 2;
    width = 70;
    height = 70;
    m_x = 0;
    m_y = 0;
    m_speed = 5;

    QString imgpath = "://resource/gif/elf_female.gif";
    m_movie = new QMovie(imgpath);
    m_movie->start();
}
