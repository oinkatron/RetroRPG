#ifndef TOOLTIP_H
#define TOOLTIP_H

#include "PopupPanel.h"

#define MAX_LINES 20

class Tooltip : public PopupPanel
{
    public:
        Tooltip();
        virtual ~Tooltip();

        void onDraw(Graphics &g);

        void maxWidth(int val) { max_width = val; }
        int maxWidth() { return max_width; }

        static Tooltip *tip_window;

    protected:
    private:
        SDL_Surface **text_lines;
        int max_width;
        int num_lines;

        void updateText();
};

#endif // TOOLTIP_H
