#include "../include/GameEvent.h"

GameEvent GameEvent::g_events;

GameEvent::GameEvent()
{
    eq_pos = 0;
}

void GameEvent::reset()
{
    for (int i = 0; i < event_queue.size(); i++)
    {
        delete event_queue[i];
    }
    event_queue.clear();

    eq_pos = 0;
}

GEvent* GameEvent::pollEvent()
{
    if (event_queue.size() > 0 && eq_pos < event_queue.size())
    {
        eq_pos++;
        return event_queue[eq_pos-1];
    }
    else
    {
        return NULL;
    }
}

GameEvent::~GameEvent()
{
    //dtor
}
