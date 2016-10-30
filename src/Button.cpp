#include "../include/Button.h"

Button::Button()
{
   action = "";
   button_img = NULL;
}

Button::Button(string capt, string act)
{
   button_img = NULL;
   action = act;
   Text(capt);

   if (text_srf)
    setDimensions(text_srf->w + 5, text_srf->h + 5);
}

Button::Button(Sprite *spr, string capt, string act)
{
    button_img = NULL;
    action = act;

    Text(capt);
    buttonSprite(spr);

    if (button_img)
    {
        setDimensions(button_img->Parent()->frameWidth(), button_img->Parent()->frameHeight());
    }
    else if (text_srf)
    {
        setDimensions(text_srf->w + 5, text_srf->h + 5);
    }
}

Button::Button(string spr_name, string capt, string act)
{
    button_img = NULL;
    action = act;
    Text(capt);
    buttonSprite(spr_name);

    if (button_img)
    {
        setDimensions(button_img->Parent()->frameWidth(), button_img->Parent()->frameHeight());
    }
    else if (text_srf)
    {
        setDimensions(text_srf->w + 5, text_srf->h + 5);
    }
}

void Button::onClick(PosObj &m_coords)
{
    clicked = true;
    GEvent *e = new GEvent;

    e->type = GE_BUTTONPRESSED;
    e->action = action;
    GameEvent::g_events.addEvent(e);

    updateText();
}

void Button::onRelease(PosObj &m_coords)
{
    GEvent *e = new GEvent;

    e->type = GE_BUTTONRELEASED;
    e->action = action;
    GameEvent::g_events.addEvent(e);

    clicked = false;
    updateText();
}

void Button::onDraw(Graphics &g)
{
    if(!hidden)
    {
        if (button_img)
        {
            int f;
            if (clicked)
            {
                f = 2;
            }
            else if (mouse_inside)
            {
                f = 1;
            }
            else
            {
                f = 0;
            }
            g.drawSprite(dimen.x, dimen.y, button_img, f);
        }
        else
        {
            Panel::onDraw(g);
            if (text_srf)
            {
                g.drawRaw(dimen.x + (dimen.w/2) - (text_srf->w/2), dimen.y + (dimen.h/2) - (text_srf->h/2), text_srf);
            }
        }
    }
}

void Button::buttonSprite(string spr_name)
{
    buttonSprite(new Sprite(dynamic_cast<SpriteBase*>(Asset::get(spr_name))));
}

void Button::buttonSprite(Sprite *spr)
{
    if (spr->Parent()->numFrames() != 3)
    {
        Log::game_log->pushLog("Cannot use Sprite for Button: Must be 3 Frames");
        delete spr;
        return;
    }

    if (button_img)
    {
        if (spr && spr->Parent() == button_img->Parent())
        {
           Log::game_log->pushLog("Same Sprite nothing to be done");
           delete spr;
           return;
        }

        delete button_img;
        button_img = NULL;
    }

    button_img = spr;
}

Button::~Button()
{
    //dtor
}
