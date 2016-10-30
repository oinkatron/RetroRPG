#ifndef EMITTER_H
#define EMITTER_H

#include <map>
#include <vector>
#include <string>

#include "Sprite.h"
#include "Log.h"
#include "Timer.h"
#include "basic_func.h"
#include "Vector2D.h"
#include "Object.h"

using namespace std;

class Particle
{
    public:
        Particle();
        virtual ~Particle();

        void onDeath();
        void onLoop();

        float x, y;
        float x_vel, y_vel;
        float x_mod, y_mod;

        SDL_Rect clip_rect;

        int life_span; //milliseconds
        int create_time;

        bool active;

        SDL_Color color;
        Sprite *sprite;
};

class Emitter : public Asset
{
    public:
        Emitter();
        virtual ~Emitter();

        static string part_path;
        static string part_exten;

        static bool onLoad(string f_name);

        //getters and setters
        void setXVelRange(float min_v, float max_v) { min_x_vel = min_v; max_x_vel = max_v;}
        void setYVelRange(float min_v, float max_v) { min_y_vel = min_v; max_y_vel = max_v;}

        int getMinXVelocity() { return min_x_vel; }
        int getMaxXVelocity() { return max_x_vel; }
        int getMinYVelocity() { return min_y_vel; }
        int getMaxYVelocity() { return max_y_vel; }

        void setXModRange(float min, float max) { min_x_mod = min; max_x_mod = max; }
        void setYModRange(float min, float max) { min_y_mod = min; max_y_mod = max; }

        float getMinXMod() { return min_x_mod; }
        float getMaxXMod() { return max_x_mod; }
        float getMinYMod() { return min_y_mod; }
        float getMaxYMod() { return max_y_mod; }

        void setLifeRange(int min_l, int max_l) { min_life = min_l; max_life = max_l; }

        int getMinLife() { return min_life; }
        int getMaxLife() { return max_life; }

        void setWidthRange(int min_s, int max_s) { min_width = min_s; max_width = max_s; }
        void setHeightRange(int min_h, int max_h) { min_height = min_h, max_height = max_h; }

        int getMinWidth() { return min_width; }
        int getMaxWidth() { return max_width; }
        int getMinHeight() { return min_height; }
        int getMaxHeight() { return max_height; }

        void setRedRange(int min, int max) { min_col.r = min; max_col.r = max; }
        void setGreenRange(int min, int max) { min_col.g = min; max_col.g = max; }
        void setBlueRange(int min, int max) { min_col.b = min; max_col.b = max; }

        int getMinRed() { return min_col.r; }
        int getMaxRed() { return max_col.r; }
        int getMinGreen() { return min_col.g; }
        int getMaxGreen() { return max_col.g; }
        int getMinBlue() { return min_col.b; }
        int getMaxBlue() { return max_col.b; }

        void setSprite(Sprite *val) { particle_sprite = val; }
        Sprite* getParticleSprite() { return particle_sprite; }

    protected:
    private:
        Sprite *particle_sprite;

        SDL_Color min_col, max_col;
        int min_blue;

        float min_x_vel, max_x_vel;
        float min_y_vel, max_y_vel;

        float min_x_mod, max_x_mod;
        float min_y_mod, max_y_mod;

        int min_life, max_life;
        int min_width, max_width;
        int min_height, max_height;
};

class Streamer
{
    public:
        Streamer();
        Streamer(string p_name, int x, int y, int w, int h, int num_parts, int sp_time, int stream_time);
        virtual ~Streamer();

        static vector<Streamer*> streamer_list;
        static Streamer* getStreamer(string s_name);

        vector<Particle*> parts;

        void onLoop();
        void onStream(int num_parts, int sp_time, int stream_time=-1);
        void stopStream();
        void onBurst(int num_parts);
        bool createParticle();
        bool resetParticle(Particle *p);

        //getter and setter
        void setPosition(int n_x, int n_y) { pos.X(n_x); pos.Y(n_y); spawn_region.x = (int)pos.X(); spawn_region.y = pos.Y(); }
        void X(float n_x) { pos.X(n_x); spawn_region.x = (int)pos.X(); }
        void Y(float n_y) { pos.Y(n_y); spawn_region.y = (int)pos.Y(); }
        float X() { return pos.X(); }
        float Y() { return pos.Y(); }
        PosObj* getPosition() { return &pos; }

        void W(int n_w) { spawn_region.w = n_w; }
        void H(int n_h) { spawn_region.h = n_h; }
        int W() { return spawn_region.w; }
        int H() { return spawn_region.h; }

        void setName(string val) { name = val; }
        string getName() { return name; }

        void setParent(string val) { parent = (Emitter*)Asset::get(val); }
        void setParent(Emitter* val) { parent = val; }
        Emitter* getParent() { return parent; }

    protected:
    private:
        string name;

        Emitter *parent;
        int max_parts;

        int start_time;
        int stream_length;

        int last_spawn;
        int spawn_rate;

        SDL_Rect spawn_region;
        PosObj pos;
 };

#endif // EMITTER_H
