#include "../include/DropDownList.h"

DropDownList* DropDownList::d_list;

DropDownList::DropDownList()
{
    host = NULL;
    margin_height = 0;
}

DropDownList::~DropDownList()
{
   reset();
}

void DropDownList::init(Panel *p, bool clr)
{
    host = p;
    if (host)
    {
        setDimensions(host->W()-host->H(), dimen.h);
        setPosition(host->screenX(), host->screenY()+host->H());
    }

    if (clr)
    {
        reset();
        setDimensions(dimen.w, 10);
    }
}

void DropDownList::addOpt(string t)
{
    SDL_Surface *tmp_msg = NULL;

   // TTF_RenderGlyph_Blended()

    //opt_off.push_back(srf);
    opt_text.push_back(t);
}

void DropDownList::onClick(PosObj &m_coords)
{
   int c_cell = m_coords.Y()/(opt_off.size()/margin_height);

   if (host)
   {
       host->Text(opt_text[c_cell]);
   }

}

void DropDownList::onRelease(PosObj &m)
{

}

void DropDownList::reset()
{
    for (int i = 0; i < opt_off.size(); i++)
    {
        if (opt_off[i])
            SDL_FreeSurface(opt_off[i]);
        if (opt_on[i])
            SDL_FreeSurface(opt_on[i]);
        if (opt_hov[i])
            SDL_FreeSurface(opt_hov[i]);
    }

    opt_off.clear();
    opt_on.clear();
    opt_hov.clear();
    sect_clicked.clear();
    sect_hovered.clear();

    margin_height = 0;
}

void DropDownList::onDraw(Graphics &g)
{
    Panel::onDraw(g);

}
