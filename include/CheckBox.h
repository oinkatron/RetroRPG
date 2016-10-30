#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "Panel.h"

class CheckBox : public Panel
{
    public:
        CheckBox();
        virtual ~CheckBox();

        void onDraw(Graphics &g);
        void onClick(PosObj &m_coords);
        void onRelease(PosObj &m_coords);

        void onKeyPress(SDLKey key, bool shift) { }
        void onEnter(PosObj &m_coords) { mouse_inside = true; }
        void onExit() { mouse_inside = false; }
        void onHover(PosObj &m_coords) { }

        bool isChecked() { return checked; }

    protected:
    private:
        bool checked;
};

#endif // CHECKBOX_H
