#include "../include/DropDownBox.h"

DropDownBox::DropDownBox()
{
    //ctor
}

DropDownBox::~DropDownBox()
{
    //dtor
}

void DropDownBox::onClick(PosObj &m_coords)
{
   if (m_coords.X() > screenX() + dimen.w - dimen.h && m_coords.X() < screenX() + dimen.w && m_coords.Y() > screenY() && m_coords.Y() < screenY() +dimen.h)
   {
       Log::game_log->pushLog("Menu opened");
   }
}

void DropDownBox::onRelease(PosObj &m_coords)
{

}

void DropDownBox::onDraw(Graphics &g)
{
    Panel::onDraw(g);

    g.setColor(0, 0, 128);
    g.drawBox((dimen.x + dimen.w)-dimen.h, dimen.y, dimen.h, dimen.h, 1);
}
