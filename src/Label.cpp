#include "../include/Label.h"

Label::Label()
{

}

Label::Label(string lbl, string fnt_name, SDL_Color txt_col)
{
    textFont(fnt_name);
    textColor(txt_col);
    Text(lbl);
}

void Label::updateText()
{
    Panel::updateText();
    if (text_srf)
    {
        dimen.w = text_srf->w;
        dimen.h = text_srf->h;
    }
    else
    {
        dimen.w = 0;
        dimen.h = 0;
    }
}

void Label::onDraw(Graphics &g)
{
    if (!hidden && text_srf)
        g.drawRaw(dimen.x, dimen.y, text_srf);
}

Label::~Label()
{
    //dtor
}
