#ifndef ALARM_H
#define ALARM_H

#include <SDL/SDL.h>
#include <vector>

using namespace std;

class Alarm
{
    public:
        Alarm(void (*trig)(void), unsigned int length);
        virtual ~Alarm();

        void onLoop(int id);

        static vector<Alarm*> alarm_bank;
    protected:
    private:
        unsigned int create_time;
        unsigned int trigger_length;

        void (*trigger)(void);
};

#endif // ALARM_H
