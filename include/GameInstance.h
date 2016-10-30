#ifndef GAMEINSTANCE_H
#define GAMEINSTANCE_H

#include <SDL/SDL.h>
#include <map>
#include <string>

#include "string_func.h"
#include "basic_func.h"
#include "DataFile.h"
#include "Log.h"
#include "Timer.h"
#include "Map.h"
#include "Image.h"
#include "Sprite.h"
#include "Camera.h"
#include "Graphics.h"
#include "Alarm.h"
#include "Emitter.h"
#include "Font.h"
#include "Object.h"
#include "PosObj.h"

#include "GameEvent.h"

#include "GameState.h"
#include "StartUpState.h"
#include "PlayState.h"
#include "MenuState.h"

#include "Panel.h"
#include "PopupPanel.h"

using namespace std;

class GameInstance
{
    public:
        GameInstance();
        virtual ~GameInstance();

        void onLoop();
        void onEvent();
        void onDraw();

        bool init();
    protected:
    private:
        static void transToPlay();

        static int screen_width;
        static int screen_height;
        static int screen_bpp;

        static int game_fps;
        static int game_speed;

        SDL_Surface *screen;
        bool done;

        Graphics g;
        SDL_Event event;

        PosObj mouse_pos;
        //Panel* sel_panel;
};

#endif // GAMEINSTANCE_H
