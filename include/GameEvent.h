#ifndef GAMEEVENT_H
#define GAMEEVENT_H

#include <vector>
#include <SDL/SDL.h>
#include <string>

#include "PosObj.h"
#include "Image.h"

using namespace std;

enum EventType
{
    GE_KEYDOWN=1,
    GE_KEYUP,
    GE_MOUSEMOVE,
    GE_MOUSEPRESSED,
    GE_MOUSERELEASED,
    GE_BUTTONPRESSED,
    GE_BUTTONRELEASED,
    GE_TEXTBOX_TEXTCHANGED,
    GE_CHATEVENT
};

struct ChatData
{
    string msg;
    string name;
    Image* portrait;
};

struct GEvent
{
    EventType type;
    PosObj *mouse_p;
    int mouse_b;
    string res_name;
    string action;
    SDLKey keycode;
    ChatData *chat_info;
};

class GameEvent
{
    public:
        virtual ~GameEvent();

        static GameEvent g_events;

        void reset();

        GEvent* pollEvent();
        void addEvent(GEvent *event) { event_queue.push_back(event); }

    protected:
        GameEvent();
    private:
        vector <GEvent*> event_queue;
        int eq_pos;
};

#endif // GAMEEVENT_H
