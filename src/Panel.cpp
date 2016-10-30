#include "../include/Panel.h"

int Panel::panel_id_num = 0;
Panel *Panel::focused_panel = NULL;
Panel *Panel::sel_panel = NULL;
Panel *Panel::hovered_panel = NULL;
vector<Panel*> Panel::panel_bank;

Font *Panel::default_font = NULL;

SDL_Color Panel::default_bg_on_color = (SDL_Color){0, 0, 0, 0};
SDL_Color Panel::default_bg_off_color = (SDL_Color){0, 0, 0, 0};
SDL_Color Panel::default_bg_pressed_color = (SDL_Color){0, 0, 0, 0};
SDL_Color Panel::default_fg_on_color = (SDL_Color){0, 0, 0, 0};
SDL_Color Panel::default_fg_off_color = (SDL_Color){0, 0, 0, 0};
SDL_Color Panel::default_fg_pressed_color = (SDL_Color){0, 0, 0, 0};
SDL_Color Panel::default_text_on_color = (SDL_Color){0, 0, 0, 0};
SDL_Color Panel::default_text_off_color = (SDL_Color){0, 0, 0, 0};
SDL_Color Panel::default_text_pressed_color = (SDL_Color){0, 0, 0, 0};
SDL_Color Panel::default_border_color = (SDL_Color){0, 0, 0, 0};

Panel::Panel()
{
    type_id = panel_id_num;
    hidden = true;

    parent_panel = NULL;

    selected = false;
    show_border = false;
    show_background = false;
    mouse_focus = false;
    mouse_inside = false;
    clicked = false;

    sel_off.setComponents(0.0f, 0.0f);

    text_srf = NULL;
    background_image = NULL;
    fnt = Panel::defaultFont();
    text = "";

    dimen.x = 0;
    dimen.y = 0;
    dimen.w = 0;
    dimen.h = 0;

    text_off_color = Panel::defaultTextOffColor();
    text_on_color = Panel::defaultTextOnColor();
    text_pressed_color = Panel::defaultTextPressedColor();

    back_on_color = Panel::defaultBackgroundOnColor();
    back_off_color = Panel::defaultBackgroundOffColor();
    back_pressed_color = Panel::defaultBackgroundPressedColor();

    border_color = (SDL_Color) {0, 0, 0, 0};
    b_width = 1;

    bg_on_set = false;
    bg_off_set = false;
    bg_pressed_set = false;

    fg_on_set = false;
    fg_off_set = false;
    fg_pressed_set = false;

    t_on_set = false;
    t_off_set = false;
    t_pressed_set = false;

    b_col_set = false;
    back_image = false;
    b_clip_set = false;
}

void Panel::addChild(Panel *p)
{
    if (p)
    {
        p->parent_panel = this;
        child_list.push_back(p);
    }
}

void Panel::updateText()
{
    if (text_srf)
    {
        SDL_FreeSurface(text_srf);
        text_srf = NULL;
    }

    if (!fnt || text == "" || text == " ")
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

    text_srf = TTF_RenderText_Solid(fnt->Raw(), text.c_str(), tmp);
}

Panel* Panel::getClickedPanel(PosObj &mouse_pos)
{
    Panel* fnd = NULL;
    for (int i = 0; i < child_list.size(); i++)
    {
        child_list[i]->X(child_list[i]->X()+dimen.x);
        child_list[i]->Y(child_list[i]->Y()+dimen.y);
        if (child_list[i]->isInside(mouse_pos.X(),mouse_pos.Y()))
        {
            fnd = child_list[i]->getClickedPanel(mouse_pos);
        }
        child_list[i]->X(child_list[i]->X()-dimen.x);
        child_list[i]->Y(child_list[i]->Y()-dimen.y);
        if (fnd)
            break;
    }

    if (fnd)
        return fnd;
    else
        return this;
}

void Panel::onKeyPress(SDLKey key, bool shift)
{

}

void Panel::onDraw(Graphics &g)
{
    if (!hidden)
    {
        if (show_background)
        {
            if (back_image)
            {
                if (b_clip_set)
                {
                    g.drawImage(dimen.x, dimen.y, background_image, &back_clip);
                }
                else
                {
                    SDL_Rect t = (SDL_Rect){0, 0, dimen.w, dimen.h};
                    g.drawImage(dimen.x, dimen.y, background_image, &t);
                }
            }
            else
            {
                if (clicked)
                {
                    if (bg_pressed_set)
                        g.setColor(back_pressed_color);
                    else
                        g.setColor(Panel::defaultBackgroundOnColor());
                }
                else if (mouse_inside)
                {
                    if (bg_on_set)
                        g.setColor(back_on_color);
                    else
                        g.setColor(Panel::defaultBackgroundOffColor());
                }
                else
                {
                    if (bg_off_set)
                        g.setColor(back_off_color);
                    else
                        g.setColor(Panel::defaultBackgroundOffColor());
                }

                g.drawRect(dimen.x, dimen.y, dimen.w, dimen.h);
            }
            if (show_border)
            {
                if (b_col_set)
                {
                   g.setColor(border_color);
                }
                else
                {
                    g.setColor(Panel::defaultBorderColor());
                }
                g.drawBox(dimen.x, dimen.y, dimen.w, dimen.h, b_width);
            }

        }

        for (int i = 0; i < child_list.size(); i++)
        {
            child_list[i]->setPosition(dimen.x+child_list[i]->X(), dimen.y+child_list[i]->Y());
            child_list[i]->onDraw(g);
            child_list[i]->setPosition(child_list[i]->X()-dimen.x, child_list[i]->Y()-dimen.y);
        }
    }
}

void Panel::onLoop()
{
    if (pos.isAnchored())
    {
        X(pos.Anchor()->X()+pos.offX());
        Y(pos.Anchor()->Y()+pos.offY());
    }
}

void Panel::onClick(PosObj &m_coords)
{
    clicked = true;
    pos.Anchor(&m_coords);

    for (int i = 0; i < Panel::panel_bank.size(); i++)
    {
        if (Panel::panel_bank[i] == this)
        {
            Panel *tmp = Panel::panel_bank[i];
            Panel::panel_bank[i] = Panel::panel_bank[Panel::panel_bank.size()-1];
            Panel::panel_bank[Panel::panel_bank.size()-1] = tmp;
        }
    }

    updateText();

}

void Panel::onRelease(PosObj &m_coords)
{
    pos.Anchor(NULL);
    clicked = false;
    updateText();
}

void Panel::onEnter(PosObj &m_pos)
{
    for (int i = 0; i < child_list.size(); i++)
    {
        child_list[i]->X(child_list[i]->X()+dimen.x);
        child_list[i]->Y(child_list[i]->Y()+dimen.y);
        if (child_list[i]->isInside(m_pos.X(), m_pos.Y()))
        {
            onExit();
            mouse_inside = false;
            child_list[i]->onEnter(m_pos);
        }
        child_list[i]->X(child_list[i]->X()-dimen.x);
        child_list[i]->Y(child_list[i]->Y()-dimen.y);
    }

    mouse_inside = true;
    updateText();
}

void Panel::onExit()
{
    clicked = false;
    mouse_inside = false;
    updateText();
}

void Panel::onHover(PosObj &m_pos)
{
    for (int i = 0; i < child_list.size(); i++)
    {
        child_list[i]->X(child_list[i]->X()+dimen.x);
        child_list[i]->Y(child_list[i]->Y()+dimen.y);
        if (child_list[i]->isInside(m_pos.X(), m_pos.Y()))
        {
            if (!child_list[i]->isEntered())
            {
                child_list[i]->onEnter(m_pos);
            }
            else
            {
                child_list[i]->onHover(m_pos);
            }
        }
        else
        {
            if (child_list[i]->isEntered())
            {
                child_list[i]->onExit();
            }
        }
        child_list[i]->X(child_list[i]->X()-dimen.x);
        child_list[i]->Y(child_list[i]->Y()-dimen.y);
    }
}

void Panel::onFocus()
{

}

void Panel::onUnfocus()
{

}

bool Panel::isInside(int x, int y)
{
    if (x > dimen.x && x < dimen.w+dimen.x && y > dimen.y && y < dimen.y + dimen.h)
    {
        return true;
    }
    return false;
}

bool Panel::isInside(SDL_Rect &obj)
{
    if (obj.x-obj.w > dimen.x && obj.x < dimen.x+dimen.w && obj.y-obj.h > dimen.y && obj.y < dimen.y + dimen.h)
    {
        return true;
    }
    return false;
}

void Panel::flush()
{
    for (int i = 0; i < panel_bank.size(); i++)
    {
        delete panel_bank[i];
    }

    panel_bank.clear();
}

Panel::~Panel()
{
    if (text_srf)
    {
        SDL_FreeSurface(text_srf);
    }

    for (int i = 0; i < child_list.size(); i++)
    {
        delete child_list[i];
    }

    child_list.clear();
}
