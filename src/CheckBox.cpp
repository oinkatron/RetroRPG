#include "../include/CheckBox.h"

CheckBox::CheckBox()
{
    checked = false;

    setDimensions(10, 10);
    backColor(255, 255, 255);
    backOnColor(128, 128, 128);
    borderColor(0, 0, 0);
    borderWidth(1);
    showBorder(true);
    showBackground(true);
}

CheckBox::~CheckBox()
{
    //dtor
}

void CheckBox::onDraw(Graphics &g)
{
    Panel::onDraw(g);

    if (checked)
    {
        g.setColor(0, 0, 128);
        g.drawRect(dimen.x+2, dimen.y+2, dimen.w - 4, dimen.h - 4);
    }

}

void CheckBox::onClick(PosObj &m_coords)
{

}

void CheckBox::onRelease(PosObj &m_coords)
{
    Log::game_log->pushLog("SupDawg");
    checked = (!checked) ? true : false;
}
