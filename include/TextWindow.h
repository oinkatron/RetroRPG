#ifndef TEXTWINDOW_H
#define TEXTWINDOW_H

#include "Panel.h"
#include "Image.h"

class TextWindow : public Panel
{
    public:
        TextWindow();
        virtual ~TextWindow();

        void initMessage(string n, string message, Image *port=NULL);
        void renderLines();

        void maxLines(int val) { max_lines = val; }
        int maxLines() { return max_lines; }

        void horizontalPadding(int val) { hor_padding = val; }
        int horizontalPadding() { return hor_padding; }

        void verticalPadding(int val) { ver_padding = val; }
        int verticalPadding() { return ver_padding; }

        void msgComplete(bool val) { msg_complete = val; }
        bool msgComplete() { return msg_complete; }

        void actionKey(SDLKey k) { act_key = k; }
        SDLKey actionKey() { return act_key; }

        void onDraw(Graphics &g);
        void onKeyPress(SDLKey key, bool shift);

    protected:
    private:
        Image *portrait;
        Image *next_icon;
        string talking_name;
        string msg;
        SDL_Surface **text_lines;
        SDL_Surface *name_txt;
        SDLKey act_key;

        int hor_padding, ver_padding;
        int txt_height;

        int msg_pos;
        int line_start;
        int ren_line;

        int max_lines; //-1 if auto determined
        int num_lines;

        bool msg_complete;

};

#endif // TEXTWINDOW_H
