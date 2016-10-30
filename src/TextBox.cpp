#include "../include/TextBox.h"

TextBox::TextBox()
{
    backColor(255, 255, 255);
    textColor(0, 0, 0);
}

void TextBox::onKeyPress(SDLKey key, bool shift)
{
    string tmp;
    switch (key)
    {
        case SDLK_a:
            if (shift)
            {
                tmp_text += "A";
            }
            else
            {
                tmp_text += "a";
            }

            break;
        case SDLK_b:
            if (shift)
                tmp_text += "B";
            else
                tmp_text += "b";
            break;
        case SDLK_c:
            if (shift)
                tmp_text += "C";
            else
                tmp_text += "c";
            break;
        case SDLK_d:
            if (shift)
                tmp_text += "D";
            else
                tmp_text += "d";
            break;
        case SDLK_e:
            if (shift)
                tmp_text += "E";
            else
                tmp_text += "e";
            break;
        case SDLK_f:
            if (shift)
                tmp_text += "F";
            else
                tmp_text += "f";
            break;
        case SDLK_g:
            if (shift)
                tmp_text += "G";
            else
                tmp_text += "g";
            break;
        case SDLK_h:
            if (shift)
                tmp_text += "H";
            else
                tmp_text += "h";
            break;
        case SDLK_i:
            if (shift)
                tmp_text += "I";
            else
                tmp_text += "i";
            break;
        case SDLK_j:
            if (shift)
                tmp_text += "J";
            else
                tmp_text += "j";
            break;
        case SDLK_k:
            if (shift)
                tmp_text += "K";
            else
                tmp_text += "k";
            break;
        case SDLK_l:
            if (shift)
                tmp_text += "L";
            else
                tmp_text += "l";
            break;
        case SDLK_m:
            if (shift)
                tmp_text += "M";
            else
                tmp_text += "m";
            break;
        case SDLK_n:
            if (shift)
                tmp_text += "N";
            else
                tmp_text += "n";
            break;
        case SDLK_o:
            if (shift)
                tmp_text += "O";
            else
                tmp_text += "o";
            break;
        case SDLK_p:
            if (shift)
                tmp_text += "P";
            else
                tmp_text += "p";
            break;
        case SDLK_q:
            if (shift)
                tmp_text += "Q";
            else
                tmp_text += "q";
            break;
        case SDLK_r:
            if (shift)
                tmp_text += "R";
            else
               tmp_text += "r";
            break;
        case SDLK_s:
            if (shift)
                tmp_text += "S";
            else
                tmp_text += "s";
            break;
        case SDLK_t:
            if (shift)
                tmp_text += "T";
            else
                tmp_text += "t";
            break;
        case SDLK_u:
            if (shift)
                tmp_text += "U";
            else
                tmp_text += "u";
            break;
        case SDLK_v:
            if (shift)
                tmp_text += "V";
            else
                tmp_text += "v";
            break;
        case SDLK_w:
            if (shift)
                tmp_text += "W";
            else
                tmp_text += "w";
            break;
        case SDLK_x:
            if (shift)
                tmp_text += "X";
            else
                tmp_text += "x";
            break;
        case SDLK_y:
            if (shift)
                tmp_text += "Y";
            else
                tmp_text += "y";
            break;
        case SDLK_z:
            if (shift)
                tmp_text += "Z";
            else
                tmp_text += "z";
            break;
        case SDLK_1:
            if (shift)
                tmp_text += "!";
            else
                tmp_text += "1";
            break;
        case SDLK_2:
            if (shift)
                tmp_text += "@";
            else
                tmp_text += "2";
            break;
        case SDLK_3:
            if (shift)
                tmp_text += "#";
            else
                tmp_text += "3";
            break;
        case SDLK_4:
            if (shift)
                tmp_text += "$";
            else
                tmp_text += "4";
            break;
        case SDLK_5:
            if (shift)
                tmp_text += "%";
            else
                tmp_text += "5";
            break;
        case SDLK_6:
            if (shift)
                tmp_text += "^";
            else
                tmp_text += "6";
            break;
        case SDLK_7:
            if (shift)
                tmp_text += "&";
            else
                tmp_text += "7";
            break;
        case SDLK_8:
            if (shift)
                tmp_text += "*";
            else
                tmp_text += "8";
            break;
        case SDLK_9:
            if (shift)
                tmp_text += "(";
            else
                tmp_text += "0";
            break;
        case SDLK_0:
            if (shift)
                tmp_text += ")";
            else
                tmp_text += "0";
            break;
        case SDLK_SEMICOLON:
            if (shift)
                tmp_text += ":";
            else
                tmp_text += ";";
            break;
        case SDLK_EQUALS:
            if (shift)
                tmp_text += "+";
            else
                tmp_text += "=";
            break;
        case SDLK_PERIOD:
            if (shift)
                tmp_text += ">";
            else
                tmp_text += ".";
            break;
        case SDLK_COMMA:
            if (shift)
                tmp_text += "<";
            else
                tmp_text += ",";
            break;
        case SDLK_SLASH:
            if (shift)
                tmp_text += "?";
            else
                tmp_text += "/";
            break;
        case SDLK_LEFTBRACKET:
            if (shift)
                tmp_text += "{";
            else
                tmp_text += "[";
            break;
        case SDLK_RIGHTBRACKET:
            if (shift)
               tmp_text += "}";
            else
                tmp_text += "]";
            break;
        case SDLK_QUOTE:
            if (shift)
                tmp_text += "\"";
            else
                tmp_text += "\'";
            break;
        case SDLK_MINUS:
            if (shift)
                tmp_text += "_";
            else
                tmp_text += "-";
            break;
        case SDLK_SPACE:
            tmp_text += " ";
            break;
        case SDLK_BACKSPACE:
            if (tmp_text.size() > 0)
            {
                tmp_text.resize(tmp_text.size()-1);
            }
            break;
        case SDLK_RETURN:
            if (Panel::focused_panel == this)
            {
                onUnfocus();
                Panel::focused_panel = NULL;
            }
        case SDLK_ESCAPE:
            if (Panel::focused_panel == this)
            {
                tmp_text = Text();
                onUnfocus();
                Panel::focused_panel = NULL;
            }

        default:
            break;
    }

    updateText();
}

void TextBox::onDraw(Graphics &g)
{
    Panel::onDraw(g);

    if (!hidden && text_srf)
    {
        if (text_srf->w >= dimen.w)
        {
            text_clip.x = text_srf->w - dimen.w;
        }
        else
        {
            text_clip.x = 0;
        }
        text_clip.y = 0;
        text_clip.h = dimen.h;
        text_clip.w = dimen.w;
        g.drawRaw(dimen.x+1, dimen.y+2, text_srf, &text_clip);
    }
}

void TextBox::updateText()
{
    if (text_srf)
    {
        SDL_FreeSurface(text_srf);
        text_srf = NULL;
    }

    string rnd_text;

    if (Panel::focused_panel == this)
    {
        rnd_text = tmp_text;
    }
    else
        rnd_text = Text();


    if (!fnt || rnd_text == "" || rnd_text == " ")
    {
        return;
    }

    SDL_Color tmp;

    if (clicked)
    {
        if (t_pressed_set)
        {
            tmp = text_pressed_color;
        }
        else
        {
            tmp = Panel::defaultTextPressedColor();
        }

    }
    else if (mouse_inside)
    {
        if (t_on_set)
        {
            tmp = text_on_color;
        }
        else
        {
            tmp = Panel::defaultTextOnColor();
        }
    }
    else
    {
        if (t_off_set)
        {
            tmp = text_off_color;
        }
        else
        {
            tmp = Panel::defaultTextOffColor();
        }
    }

    text_srf = TTF_RenderText_Solid(fnt->Raw(), rnd_text.c_str(), tmp);
}

void TextBox::onFocus()
{
   tmp_text = Text();
}

void TextBox::onUnfocus()
{
    if (tmp_text != Text())
    {
        Text(tmp_text);

        GEvent *new_ev = new GEvent;
        new_ev->action = action;
        new_ev->type = GE_TEXTBOX_TEXTCHANGED;

        GameEvent::g_events.addEvent(new_ev);
    }
}

TextBox::~TextBox()
{
    //dtor
}
