#ifndef TIMER_H
#define TIMER_H

#include <SDL/SDL.h>

using namespace std;

class Timer
{
    public:
        static Timer fps;

        Timer();
        virtual ~Timer();

        void onLoop();
        void start();
        void start(int run_time);

        int getTicks() { return SDL_GetTicks() - start_time; }
        bool timeUp() { return (SDL_GetTicks()-start_time >= time_limit ); }

        void limitFPS();

        void setFPS(int new_rate) { if (new_rate == 0) frame_rate = 0; else frame_rate = 1000/new_rate; }

        int getFPS() { return num_frames; }
        float getSpeedFactor(float modifier) { return speed_factor * modifier * game_speed; }

        float getGameSpeed() { return game_speed; }
        void setGameSpeed(float val) { game_speed = val;}

    protected:
    private:
        unsigned int last_time;
        unsigned int old_time;
        unsigned int start_time;

        int frame_rate;
        float speed_factor;
        float game_speed;

        int num_frames;
        int frames;

        int time_limit;
};

#endif // TIMER_H
