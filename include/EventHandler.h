#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <SDL/SDL.h>
#include <vector>

using namespace std;

enum EventType
{
    NULL_EVENT,
    KEY_EVENT,
    MOUSE_EVENT,
    MOUSE_MOTION_EVENT
};

enum OButton
{
    OButton_NULL = -1,
    OButton_LEFT = 1,
    OButton_MIDDLE,
    OButton_RIGHT
};

enum OKey
{
    OKey_NULL = -1,
    OKey_UP = SDLK_UP,
    OKey_DOWN = SDLK_DOWN,
    OKey_RIGHT = SDLK_RIGHT,
    OKey_LEFT = SDLK_LEFT,
    OKey_a = SDLK_a,
    OKey_b = SDLK_b,
    OKey_c = SDLK_c,
    OKey_d = SDLK_d,
    OKey_e = SDLK_e,
    OKey_f = SDLK_f,
    OKey_g = SDLK_g,
    OKey_h = SDLK_h,
    OKey_i = SDLK_i,
    OKey_j = SDLK_j,
    OKey_k = SDLK_k,
    OKey_l = SDLK_l,
    OKey_m = SDLK_m,
    OKey_n = SDLK_n,
    OKey_o = SDLK_o,
    OKey_p = SDLK_p,
    OKey_q = SDLK_q,
    OKey_r = SDLK_r,
    OKey_s = SDLK_s,
    OKey_t = SDLK_t,
    OKey_u = SDLK_u,
    OKey_v = SDLK_v,
    OKey_w = SDLK_w,
    OKey_x = SDLK_x,
    OKey_y = SDLK_y,
    OKey_z = SDLK_z
};

struct OEvent
{
    EventType type;
    OKey key;

    OButton button;
    int x, y;

    bool pressed;
};

class EventHandler
{
    public:
        EventHandler();
        virtual ~EventHandler();

        bool pushEvent(SDL_Event* e);
        OEvent* popEvent();

    protected:
    private:
        vector<OEvent*> event_queue;
        int event_marker;
};

#endif // EVENTHANDLER_H
