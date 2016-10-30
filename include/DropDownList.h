#ifndef DROPDOWNLIST_H
#define DROPDOWNLIST_H

#include "PopupPanel.h"


class DropDownList : private PopupPanel
{
    public:
        DropDownList();
        virtual ~DropDownList();

        static DropDownList *d_list;

        void init(Panel *p, bool clr=true);

        void onDraw(Graphics &g);
        void onClick(PosObj &m_coords);
        void onRelease(PosObj &m_coords);

        void addOpt(string txt);

    protected:
    private:
        vector<SDL_Surface*>opt_off;
        vector<SDL_Surface*>opt_on;
        vector<SDL_Surface*>opt_hov;

        vector<string> opt_text;
        vector<bool> sect_hovered;
        vector<bool> sect_clicked;
        Panel *host;
        int margin_height;

        void reset();
};

#endif // DROPDOWNLIST_H
