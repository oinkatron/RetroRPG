#ifndef CAMERA_H
#define CAMERA_H

#include <SDL/SDL.h>

#include "Object.h"
#include "Log.h"

class Camera
{
    public:
        Camera();
        virtual ~Camera();

        static Camera cam;

        bool init(int width, int height);
        void onLoop();

        //Getters and Setters
        SDL_Rect& gameClip() { return game_view; }

        void setPosition(int new_x, int new_y);

        void X(int val) { setPosition(val, game_view.y); }
        int X() { return game_view.x; }

        void Y(int val) { setPosition(game_view.x, val); }
        int Y() { return game_view.y; }

        int W() { return game_view.w; }
        int H() { return game_view.h; }

        bool isInside(int x, int y);
        bool isInside(SDL_Rect &obj);

        void follow(Object* val) { follow_me = val; }
        Object* follow() { return follow_me; }

        void setObjectBounds(int x_pad, int y_pad);

    protected:
    private:
        SDL_Rect game_view;
        int pad_x, pad_y;

        Object* follow_me;
};

#endif // CAMERA_H
