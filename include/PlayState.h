#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "GameState.h"
#include "Camera.h"
#include "Map.h"
#include "Player.h"
#include "Panel.h"
#include "Label.h"
#include "Button.h"
#include "TextWindow.h"
#include "PosObj.h"


class PlayState : public GameState
{
    public:
        PlayState();
        virtual ~PlayState();

        static PlayState play_state;

        void onLoop();
        void onDraw(Graphics &g);
        void onEvent(GameEvent *ge);
        void onLoad();
        void onUnload();

        void toggleDebug() { if (debug_mode) debug_mode = false; else debug_mode = true; }
        bool debugging() { return debug_mode; }

        void setMap(Map *val) { m_map = val;}

    protected:
    private:
        Map *m_map;

        PosObj mouse_p;
        TextWindow *text_box;

        Player *p;

        Object *selected_obj;
        map<string, Object*>::iterator obj_itr;

        SDL_Rect clip;
        bool debug_mode;
        bool chat_active;
};

#endif // PLAYSTATE_H
