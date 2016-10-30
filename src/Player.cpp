#include "../include/Player.h"

int Player::player_id = 1;

Player::~Player()
{
    //dtor
}

void Player::handleKeyInput(SDLKey key, bool pressed)
{
    ObjNPC::handleKeyInput(key, pressed);

    if (key == controls.actionA() && pressed)
    {
        vector<Object*> o_list;
        switch (cur_dir)
        {
            case DIR_DOWN:
                o_list = Object::getObjectsInRect(mapX()*local->tileSize(), (mapY()+1) * local->tileSize(), local->tileSize(), local->tileSize());
                if (o_list.size() == 1 && o_list[0] != this)
                {
                   GEvent *new_ev = new GEvent;
                   new_ev->type = GE_CHATEVENT;
                   new_ev->chat_info = new ChatData;
                   new_ev->chat_info->msg = dynamic_cast<ObjNPC*>(o_list[0])->chatText();
                   new_ev->chat_info->name = dynamic_cast<ObjNPC*>(o_list[0])->charName();
                   new_ev->chat_info->portrait = dynamic_cast<ObjNPC*>(o_list[0])->chatPortrait();
                   Log::game_log->pushLog("Oink?");
                   GameEvent::g_events.addEvent(new_ev);
                }
                else if (o_list.size() == 2)
                {
                    if (o_list[0] == this)
                    {
                       GEvent *new_ev = new GEvent;
                       new_ev->type = GE_CHATEVENT;
                       new_ev->chat_info = new ChatData;
                       new_ev->chat_info->msg = dynamic_cast<ObjNPC*>(o_list[1])->chatText();
                       new_ev->chat_info->name = dynamic_cast<ObjNPC*>(o_list[1])->charName();
                       new_ev->chat_info->portrait = dynamic_cast<ObjNPC*>(o_list[1])->chatPortrait();
                       GameEvent::g_events.addEvent(new_ev);

                    }
                    else
                    {
                       GEvent *new_ev = new GEvent;
                       new_ev->type = GE_CHATEVENT;
                       new_ev->chat_info = new ChatData;
                       new_ev->chat_info->msg = dynamic_cast<ObjNPC*>(o_list[0])->chatText();
                       new_ev->chat_info->name = dynamic_cast<ObjNPC*>(o_list[0])->charName();
                       new_ev->chat_info->portrait = dynamic_cast<ObjNPC*>(o_list[0])->chatPortrait();
                       GameEvent::g_events.addEvent(new_ev);

                    }
                }
                else if ( o_list.size() > 2)
                {
                    ObjNPC* closest;
                    int tmp;
                    int close_i = 9999;

                    for (int i = 0; i < o_list.size(); i++)
                    {
                        if (o_list[i] != this)
                        {
                            tmp = PosObj::distanceSqrd(o_list[i]->getPosition(), this->getPosition());
                            if (tmp < close_i)
                            {
                                close_i = tmp;
                                closest = (ObjNPC*)o_list[i];
                            }

                        }
                    }

                    GEvent *new_ev = new GEvent;
                    new_ev->type = GE_CHATEVENT;
                    new_ev->chat_info = new ChatData;
                    new_ev->chat_info->msg = closest->chatText();
                    new_ev->chat_info->name = closest->charName();
                    new_ev->chat_info->portrait = closest->chatPortrait();
                    GameEvent::g_events.addEvent(new_ev);
                }
                break;
            case DIR_UP:
                o_list = Object::getObjectsInRect(mapX()*local->tileSize(), (mapY() - 1)* local->tileSize(), local->tileSize(), local->tileSize());
                if (o_list.size() == 1 && o_list[0] != this)
                {
                   GEvent *new_ev = new GEvent;
                   new_ev->type = GE_CHATEVENT;
                   new_ev->chat_info = new ChatData;
                   new_ev->chat_info->msg = dynamic_cast<ObjNPC*>(o_list[0])->chatText();
                   new_ev->chat_info->name = dynamic_cast<ObjNPC*>(o_list[0])->charName();
                   new_ev->chat_info->portrait = dynamic_cast<ObjNPC*>(o_list[0])->chatPortrait();
                   Log::game_log->pushLog("Oink?");
                   GameEvent::g_events.addEvent(new_ev);
                }
                else if (o_list.size() == 2)
                {
                    if (o_list[0] == this)
                    {
                       GEvent *new_ev = new GEvent;
                       new_ev->type = GE_CHATEVENT;
                       new_ev->chat_info = new ChatData;
                       new_ev->chat_info->msg = dynamic_cast<ObjNPC*>(o_list[1])->chatText();
                       new_ev->chat_info->name = dynamic_cast<ObjNPC*>(o_list[1])->charName();
                       new_ev->chat_info->portrait = dynamic_cast<ObjNPC*>(o_list[1])->chatPortrait();
                       GameEvent::g_events.addEvent(new_ev);

                    }
                    else
                    {
                       GEvent *new_ev = new GEvent;
                       new_ev->type = GE_CHATEVENT;
                       new_ev->chat_info = new ChatData;
                       new_ev->chat_info->msg = dynamic_cast<ObjNPC*>(o_list[0])->chatText();
                       new_ev->chat_info->name = dynamic_cast<ObjNPC*>(o_list[0])->charName();
                       new_ev->chat_info->portrait = dynamic_cast<ObjNPC*>(o_list[0])->chatPortrait();
                       GameEvent::g_events.addEvent(new_ev);

                    }
                }
                else if ( o_list.size() > 2)
                {
                    ObjNPC* closest;
                    int tmp;
                    int close_i = 9999;

                    for (int i = 0; i < o_list.size(); i++)
                    {
                        if (o_list[i] != this)
                        {
                            tmp = PosObj::distanceSqrd(o_list[i]->getPosition(), this->getPosition());
                            if (tmp < close_i)
                            {
                                close_i = tmp;
                                closest = (ObjNPC*)o_list[i];
                            }

                        }
                    }

                    GEvent *new_ev = new GEvent;
                    new_ev->type = GE_CHATEVENT;
                    new_ev->chat_info = new ChatData;
                    new_ev->chat_info->msg = closest->chatText();
                    new_ev->chat_info->name = closest->charName();
                    new_ev->chat_info->portrait = closest->chatPortrait();
                    GameEvent::g_events.addEvent(new_ev);
                }
                break;
            case DIR_LEFT:
                o_list = Object::getObjectsInRect((mapX()-1)*local->tileSize(), mapY()* local->tileSize(), local->tileSize(), local->tileSize());
                if (o_list.size() == 1 && o_list[0] != this)
                {
                   GEvent *new_ev = new GEvent;
                   new_ev->type = GE_CHATEVENT;
                   new_ev->chat_info = new ChatData;
                   new_ev->chat_info->msg = dynamic_cast<ObjNPC*>(o_list[0])->chatText();
                   new_ev->chat_info->name = dynamic_cast<ObjNPC*>(o_list[0])->charName();
                   new_ev->chat_info->portrait = dynamic_cast<ObjNPC*>(o_list[0])->chatPortrait();
                   Log::game_log->pushLog("Oink?");
                   GameEvent::g_events.addEvent(new_ev);
                }
                else if (o_list.size() == 2)
                {
                    if (o_list[0] == this)
                    {
                       GEvent *new_ev = new GEvent;
                       new_ev->type = GE_CHATEVENT;
                       new_ev->chat_info = new ChatData;
                       new_ev->chat_info->msg = dynamic_cast<ObjNPC*>(o_list[1])->chatText();
                       new_ev->chat_info->name = dynamic_cast<ObjNPC*>(o_list[1])->charName();
                       new_ev->chat_info->portrait = dynamic_cast<ObjNPC*>(o_list[1])->chatPortrait();
                       GameEvent::g_events.addEvent(new_ev);

                    }
                    else
                    {
                       GEvent *new_ev = new GEvent;
                       new_ev->type = GE_CHATEVENT;
                       new_ev->chat_info = new ChatData;
                       new_ev->chat_info->msg = dynamic_cast<ObjNPC*>(o_list[0])->chatText();
                       new_ev->chat_info->name = dynamic_cast<ObjNPC*>(o_list[0])->charName();
                       new_ev->chat_info->portrait = dynamic_cast<ObjNPC*>(o_list[0])->chatPortrait();
                       GameEvent::g_events.addEvent(new_ev);

                    }
                }
                else if ( o_list.size() > 2)
                {
                    ObjNPC* closest;
                    int tmp;
                    int close_i = 9999;

                    for (int i = 0; i < o_list.size(); i++)
                    {
                        if (o_list[i] != this)
                        {
                            tmp = PosObj::distanceSqrd(o_list[i]->getPosition(), this->getPosition());
                            if (tmp < close_i)
                            {
                                close_i = tmp;
                                closest = (ObjNPC*)o_list[i];
                            }

                        }
                    }

                    GEvent *new_ev = new GEvent;
                    new_ev->type = GE_CHATEVENT;
                    new_ev->chat_info = new ChatData;
                    new_ev->chat_info->msg = closest->chatText();
                    new_ev->chat_info->name = closest->charName();
                    new_ev->chat_info->portrait = closest->chatPortrait();
                    GameEvent::g_events.addEvent(new_ev);
                }
                break;
            case DIR_RIGHT:
                o_list = Object::getObjectsInRect((mapX()+1)*local->tileSize(), mapY()* local->tileSize(), local->tileSize(), local->tileSize());
                if (o_list.size() == 1 && o_list[0] != this)
                {
                   GEvent *new_ev = new GEvent;
                   new_ev->type = GE_CHATEVENT;
                   new_ev->chat_info = new ChatData;
                   new_ev->chat_info->msg = dynamic_cast<ObjNPC*>(o_list[0])->chatText();
                   new_ev->chat_info->name = dynamic_cast<ObjNPC*>(o_list[0])->charName();
                   new_ev->chat_info->portrait = dynamic_cast<ObjNPC*>(o_list[0])->chatPortrait();
                   Log::game_log->pushLog("Oink?");
                   GameEvent::g_events.addEvent(new_ev);
                }
                else if (o_list.size() == 2)
                {
                    if (o_list[0] == this)
                    {
                       GEvent *new_ev = new GEvent;
                       new_ev->type = GE_CHATEVENT;
                       new_ev->chat_info = new ChatData;
                       new_ev->chat_info->msg = dynamic_cast<ObjNPC*>(o_list[1])->chatText();
                       new_ev->chat_info->name = dynamic_cast<ObjNPC*>(o_list[1])->charName();
                       new_ev->chat_info->portrait = dynamic_cast<ObjNPC*>(o_list[1])->chatPortrait();
                       GameEvent::g_events.addEvent(new_ev);

                    }
                    else
                    {
                       GEvent *new_ev = new GEvent;
                       new_ev->type = GE_CHATEVENT;
                       new_ev->chat_info = new ChatData;
                       new_ev->chat_info->msg = dynamic_cast<ObjNPC*>(o_list[0])->chatText();
                       new_ev->chat_info->name = dynamic_cast<ObjNPC*>(o_list[0])->charName();
                       new_ev->chat_info->portrait = dynamic_cast<ObjNPC*>(o_list[0])->chatPortrait();
                       GameEvent::g_events.addEvent(new_ev);

                    }
                }
                else if ( o_list.size() > 2)
                {
                    ObjNPC* closest;
                    int tmp;
                    int close_i = 9999;

                    for (int i = 0; i < o_list.size(); i++)
                    {
                        if (o_list[i] != this)
                        {
                            tmp = PosObj::distanceSqrd(o_list[i]->getPosition(), this->getPosition());
                            if (tmp < close_i)
                            {
                                close_i = tmp;
                                closest = (ObjNPC*)o_list[i];
                            }

                        }
                    }

                    GEvent *new_ev = new GEvent;
                    new_ev->type = GE_CHATEVENT;
                    new_ev->chat_info = new ChatData;
                    new_ev->chat_info->msg = closest->chatText();
                    new_ev->chat_info->name = closest->charName();
                    new_ev->chat_info->portrait = closest->chatPortrait();
                    GameEvent::g_events.addEvent(new_ev);
                }
                break;
        }
    }
}

void Player::onLoop()
{
    if (!(Velocity().x == 0 && Velocity().y == 0))
    {
        onMove();
    }
}
