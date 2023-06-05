#include "playerelf.h"

playerelf::playerelf()
{
    m_type = 1;
    m_hp = 10;
    m_attack = 3;
    width = 70;
    height = 120;
    m_x = 0;
    m_y = 0;
    m_speed = 2;

    QString imgpath = "://resource/gif/elf_female_run.gif";
    m_movie = new QMovie(imgpath);
    m_movie->start();
}
