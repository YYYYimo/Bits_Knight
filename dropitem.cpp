#include "dropitem.h"

DropItem::DropItem(int t)
{
    type = t;
    switch(t)
    {
    case red:
       imgpath = "://resource/img/flask_big_red.png"; break;
    case blue:
        imgpath = "://resource/img/flask_big_blue.png"; break;
    case yellow:

    }
}