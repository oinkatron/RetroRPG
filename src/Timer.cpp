#include "../include/Timer.h"

Timer Timer::fps;

Timer::Timer()
{
    frames = 0;
    num_frames = 0;

    frame_rate = 0.0f;

    old_time = 0;
    last_time = 0;
    start_time = 0;

    speed_factor = 0.0f;
    game_speed = 1.0f;

    time_limit = 0;
}

void Timer::start()
{
    start_time = SDL_GetTicks();
}

void Timer::start(int run_time)
{
    start_time = SDL_GetTicks();
    time_limit = run_time;
}

void Timer::limitFPS()
{
    if (!(frame_rate <= 0))
    {
        if (SDL_GetTicks() - start_time < frame_rate)
        {
            SDL_Delay(frame_rate - (SDL_GetTicks() - start_time));
        }
    }
}

void Timer::onLoop()
{
    if (1000 < SDL_GetTicks() - old_time)
    {
        old_time = SDL_GetTicks();
        num_frames = frames;
        frames = 0;
    }

    speed_factor = (SDL_GetTicks() - last_time) / 1000.0f;
    last_time = SDL_GetTicks();

    frames++;
}

Timer::~Timer()
{
    //dtor
}
