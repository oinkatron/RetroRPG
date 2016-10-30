#include "../include/Tooltip.h"

Tooltip* Tooltip::tip_window = NULL;

Tooltip::Tooltip()
{
    text_lines = NULL;
    num_lines = 0;
    max_width = -1;
}

Tooltip::~Tooltip()
{
    //dtor
}

void Tooltip::onDraw(Graphics &g)
{
    if (!hidden && !(Text() == " " || Text() == ""))
    {
        Panel::onDraw(g);

        if (text_lines)
        {
            for (int i = 0; i < num_lines; i++)
            {
                g.drawRaw(dimen.x + 1, dimen.y + (i*(text_lines[i]->h+1))+1, text_lines[i]);
            }

        }

    }
}

void Tooltip::updateText()
{
    int tmp_w = 0, tmp_h = 0;
    int line_start = 0, ren_line = 0;
    int msg_pos = 0, old_msg_pos = 0;

    string msg = Text();

    if (text_lines)
    {
        for (int i = 0; i < num_lines; i++)
        {
            if (text_lines[i])
            {
                SDL_FreeSurface(text_lines[i]);
                text_lines[i] = NULL;
            }

            delete [] text_lines;

            text_lines = new SDL_Surface*[10];
            for (int i = 0; i < 10; i++)
            {
                text_lines[i] = NULL;
            }

        }
    }

    text_lines = new SDL_Surface*[MAX_LINES];
    for (int i = 0; i < MAX_LINES; i++)
    {
        text_lines[i] = NULL;
    }
    num_lines = 0;

    if (msg == "" || msg == " ")
    {
        return;
    }
    else
    {
        if (max_width == -1)
        {
            text_lines = new SDL_Surface*[1];
            text_lines[0] = TTF_RenderText_Solid(fnt->Raw(), msg.c_str(), text_off_color);
            setDimensions(text_lines[0]->w - 2, text_lines[0]->h - 2);
            num_lines = 1;
        }
        else
        {
            while((msg_pos = msg.find(" ", msg_pos+1)) != string::npos)
            {
                TTF_SizeText(fnt->Raw(), msg.substr(line_start, msg_pos-line_start).c_str(), &tmp_w, &tmp_h);
                if (tmp_w > max_width - 2)
                {
                    text_lines[ren_line] = TTF_RenderText_Solid(fnt->Raw(), msg.substr(line_start, old_msg_pos-line_start).c_str(), text_off_color);
                    ren_line++;
                    line_start = old_msg_pos+1;
                    if (ren_line == MAX_LINES - 1)
                        break;
                }
                else if (tmp_w == max_width - 2)
                {
                    text_lines[ren_line] = TTF_RenderText_Solid(fnt->Raw(), msg.substr(line_start, msg_pos-line_start).c_str(), text_off_color);
                    ren_line++;
                    line_start = msg_pos+1;
                    if (ren_line == MAX_LINES - 1)
                        break;
                }

                old_msg_pos = msg_pos;
            }

            text_lines[ren_line] = TTF_RenderText_Solid(fnt->Raw(), msg.substr(line_start, msg.size()-line_start).c_str(), text_off_color);
            num_lines = ren_line + 1;
            if (num_lines == 1)
                setDimensions(text_lines[ren_line]->w + 2, (text_lines[ren_line]->h+2) * num_lines);
            else
                setDimensions(max_width + 2, (text_lines[ren_line]->h+2) * num_lines);
        }

    }

}
