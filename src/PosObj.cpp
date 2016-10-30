#include "../include/PosObj.h"

PosObj::PosObj()
{
    pos.setComponents(0.0f, 0.0f);
    old_pos.setComponents(0.0f, 0.0f);
    fllw = NULL;
    fllw_offset.setComponents(0.0f, 0.0f);
}

PosObj::~PosObj()
{
    //dtor
}

void PosObj::Anchor(PosObj *p)
{
    if (p)
    {
        fllw = p;
        fllw_offset.setComponents(pos.x-p->X(), pos.y-p->Y());
    }
    else
    {
        fllw_offset.setComponents(0.0f, 0.0f);
        fllw = NULL;
    }
}

void PosObj::Anchor(PosObj *p, float x_off, float y_off)
{
    if (p)
    {
        fllw = p;
        fllw_offset.setComponents(x_off, y_off);
    }
    else
    {
        fllw_offset.setComponents(x_off, y_off);
        fllw = NULL;
    }
}
