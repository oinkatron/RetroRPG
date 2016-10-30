#ifndef LABEL_H
#define LABEL_H

#include "Panel.h"


class Label : public Panel
{
    public:
        Label();
        Label(string lbl, string fnt_name, SDL_Color col);
        virtual ~Label();

        void onDraw(Graphics &g);

        void onKeyPress(SDLKey key, bool shift) { }
        void onClick(PosObj &m_coords){ clicked = true; }
        void onRelease(PosObj &m_coords) { clicked = false; }
        void onEnter(PosObj &m_coords) { mouse_inside = true; }
        void onExit() { mouse_inside = false; }
        void onHover(PosObj &m_coords) { }

    protected:
    private:
        void updateText();
};

#endif // LABEL_H
