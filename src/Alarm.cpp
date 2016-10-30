#include "../include/Alarm.h"

vector<Alarm*> Alarm::alarm_bank;

Alarm::Alarm(void (*trig)(void), unsigned int length)
{
    trigger = trig;

    create_time = SDL_GetTicks();
    trigger_length = length;

    alarm_bank.push_back(this);
}

void Alarm::onLoop(int id)
{
    if (SDL_GetTicks()-create_time > trigger_length)
    {
        trigger();
        alarm_bank.erase(alarm_bank.begin()+id);
    }
}

Alarm::~Alarm()
{
    //dtor
}
