#ifndef SPRITE_H
#define SPRITE_H

#include <SDL/SDL.h>

#include <string>

#include "Asset.h"
#include "Image.h"
#include "DataFile.h"
#include "Timer.h"

using namespace std;

class SpriteBase : public Asset
{
    public:
        SpriteBase();
        virtual ~SpriteBase();

        static bool onLoad(string f_name);
        static string dir;
        static string exten;

        //Getters and Setters
        void Raw(Image *img) { sheet = img; }
        void Raw(string i_name) { sheet = (Image*)Asset::get(i_name); }
        Image *Raw() { return sheet; }

        void initFrames();

        int startX() { return start_frame_x; }
        void startX(int val) { start_frame_x = val; }

        int startY() { return start_frame_y; }
        void startY(int val) { start_frame_y = val; }

        int frameWidth() { return frame_width; }
        void frameWidth(int val) { frame_width = val; }

        int frameHeight() { return frame_height; }
        void frameHeight(int val) { frame_height = val; }

        int numFrames() { return num_frames; }
        void numFrames(int val) { num_frames = val; }
        SDL_Rect* Frames() { return frames; }

        bool horizontalOrientation() { return horizontal; }
        void horizontalOrientation(bool val) { horizontal = val; }

        int defaultAnimationSpeed() { return def_anim_ticks; }
        void defaultAnimationSpeed(int val) { def_anim_ticks = val; }

    protected:
    private:
        Image *sheet;
        SDL_Rect *frames;

        int start_frame_x;
        int start_frame_y;

        int frame_width;
        int frame_height;

        int num_frames;

        int def_anim_ticks;

        bool horizontal;
};

class Sprite
{
    public:
        Sprite(SpriteBase *sb);
        Sprite(string spr_b_name);
        virtual ~Sprite();

        void currentFrameNumber(int val) { cur_frame = val; }
        int  currentFrameNumber() { return cur_frame; }
        SDL_Rect getFrame(int frame_num);
        SDL_Rect getNextFrame();

        //Getters and Setters
        void Speed(int val) { anim_ticks = val; }
        int Speed() { return anim_ticks; }

        void Parent(SpriteBase* sb) {parent = sb; }
        SpriteBase* Parent() { return parent; }

    protected:
    private:
        SpriteBase *parent;

        int cur_frame;

        int anim_ticks; //Milliseconds a frame
        int start_ticks;
};

#endif // SPRITE_H
