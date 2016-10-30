#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "Panel.h"

class TextBox : public Panel
{
    public:
        TextBox();
        virtual ~TextBox();

        void onKeyPress(SDLKey key, bool shift);
        void onFocus();
        void onUnfocus();
        void onDraw(Graphics &g);

        void onClick(PosObj &m_coords){ clicked = true; }
        void onRelease(PosObj &m_coords) { clicked = false; }
        void onEnter(PosObj &m_coords) { mouse_inside = true; }
        void onExit() { mouse_inside = false; }
        void onHover(PosObj &m_coords) { }

        void Action(string str) { action = str; }
        string Action() { return action; }

    protected:
    private:
        SDL_Rect text_clip;

        string action;
        string tmp_text;

        int cursur_pos;
        int txt_off;

        void updateText();
};

#endif // TEXTBOX_H
