#include "../include/TextWindow.h"

TextWindow::TextWindow()
{
    portrait = NULL;
    next_icon = NULL;

    hor_padding = 0;
    ver_padding = 0;

    txt_height = 0;

    num_lines = 0;
    max_lines = 1;

    text_lines = NULL;
    name_txt = NULL;


    talking_name = "";
    msg = "";
    msg_pos = 0;

    line_start = 0;
    ren_line = 0;
    msg_complete = false;
}

TextWindow::~TextWindow()
{
    //dtor
}

void TextWindow::onDraw(Graphics &g)
{
    if (!hidden)
    {
        Panel::onDraw(g);

        for (int i = 0; i < num_lines; i++)
        {
            if (text_lines[i])
               g.drawRaw((dimen.x + (dimen.w/2)) - (text_lines[i]->w/2), dimen.y + ver_padding + (i * (txt_height+ver_padding)), text_lines[i], NULL);
        }

        if (portrait)
        {
            g.drawImage(dimen.x, dimen.y, portrait);
        }

        if (name_txt)
        {
            g.drawRaw(dimen.x+30 - (name_txt->w/2), dimen.y + 60, name_txt);
        }
    }
}

void TextWindow::onKeyPress(SDLKey key, bool shift)
{
    if (key == act_key)
    {
        if (msg_complete)
        {
            Panel::focused_panel = NULL;
            hidden = true;
        }
        else
        {
            renderLines();
        }
    }
}

void TextWindow::renderLines()
{
    int tmp_w = 0;
    ren_line = 0;

    bool erly_brk = false;

    for (int i = 0; i < num_lines; i++)
    {
        if (text_lines[i])
        {
            SDL_FreeSurface(text_lines[i]);
            text_lines[i] = NULL;
        }
    }

    for (int i = line_start+1; i <= msg.size(); i++)
    {
        if (i > line_start)
        {
            TTF_SizeText(fnt->Raw(), msg.substr(line_start, i-line_start).c_str(), &tmp_w, &txt_height);
            if (tmp_w >= dimen.w - (hor_padding*2))
            {
                //render this line and reset word_cnt
                if (msg_pos - line_start <= 0)
                {
                    text_lines[ren_line] = TTF_RenderText_Solid(fnt->Raw(), msg.substr(line_start, i-line_start-1).c_str(), text_off_color);
                    line_start = i;
                }
                else
                {
                    text_lines[ren_line] = TTF_RenderText_Solid(fnt->Raw(), msg.substr(line_start, msg_pos-line_start).c_str(), text_off_color);
                    line_start = msg_pos+1;
                }

                ren_line++;

                if (ren_line >= num_lines)
                {
                    erly_brk = true;
                    break;
                }
            }
            else
            {
                if (i == msg.size())
                {
                    text_lines[ren_line] = TTF_RenderText_Solid(fnt->Raw(), msg.substr(line_start, i - line_start).c_str(), text_off_color);
                    ren_line++;
                }

                if (msg[i] == ' ')
                {
                    msg_pos = i;
                }
            }
        }
    }

    if (!erly_brk)
    {
        msg_complete = true;
    }
}

void TextWindow::initMessage(string n, string message, Image *port)
{
    ren_line = 0;
    msg_pos = 0;
    line_start = 0;

    msg_complete = false;

    msg = message;
    talking_name = n;

    portrait = port;

    if (name_txt)
    {
        SDL_FreeSurface(name_txt);
        name_txt = NULL;
    }

    if (n != "" && n != " ")
    {
        name_txt = TTF_RenderText_Solid(fnt->Raw(), n.c_str(), text_off_color);
    }

    if(!text_lines)
    {
        if (max_lines == -1)
            num_lines = dimen.h / fnt->Size();
        else
            num_lines = max_lines;

        //Log::game_log->pushLog("Number of lines: " + toString(dimen.h) + " / " + toString(fnt->Size()) + " = " + toString(num_lines));

        text_lines = new SDL_Surface*[num_lines];
        for (int i = 0; i < num_lines; i++)
        {
            text_lines[i] = NULL;
        }
    }
    else
    {
        if (max_lines == -1)
        {
            for (int i = 0; i < num_lines; i++)
            {
                if (text_lines[i])
                {
                    SDL_FreeSurface(text_lines[i]);
                    text_lines[i] = NULL;
                }
            }

            num_lines = dimen.h / fnt->Size();
        }
        else
        {
            for (int i = 0; i < max_lines; i++)
            {
                if (text_lines[i])
                {
                    SDL_FreeSurface(text_lines[i]);
                    text_lines[i] = NULL;
                }
            }
            num_lines = max_lines;
        }
    }
}
