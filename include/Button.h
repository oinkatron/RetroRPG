#ifndef BUTTON_H
#define BUTTON_H

#include "Panel.h"
#include "Tooltip.h"
#include "Sprite.h"

class Button : public Panel
{
    public:
        Button();
        Button(string capt, string action);
        Button(Sprite *spr, string capt, string action);
        Button(string spr_name, string capt, string action);

        virtual ~Button();

        void onClick(PosObj &m_coords);
        void onRelease(PosObj &m_coords);
        void onDraw(Graphics &g);

        void buttonSprite (Sprite *spr);
        void buttonSprite (string spr_name);

        void onKeyPress(SDLKey key, bool shift) { }
        void onEnter(PosObj &m_coords) { mouse_inside = true; if (Tooltip::tip_window) { Tooltip::tip_window->Text(tooltip_text); Tooltip::tip_window->Hidden(false); } }
        void onExit() { mouse_inside = false; if (Tooltip::tip_window) Tooltip::tip_window->Hidden(true); }
        void onHover(PosObj &m_coords) { }
        void onFocus() { }
        void onUnfocus() { }

        void setAction(string a) { action = a; }

    protected:
    private:
        //int b_state;
        string action;
        Sprite *button_img;
};

#endif // BUTTON_H
