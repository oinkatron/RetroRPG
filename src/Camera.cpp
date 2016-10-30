#include "../include/Camera.h"

Camera Camera::cam;

Camera::Camera()
{
    game_view = (SDL_Rect){0, 0, 0, 0};


    follow_me = NULL;
}

Camera::~Camera()
{

}

void Camera::onLoop()
{
    if (follow_me)
    {
        SDL_Rect obj_bounds;
        obj_bounds = follow_me->getBounds();
        if (game_view.x + pad_x > obj_bounds.x)
        {
            game_view.x = obj_bounds.x - pad_x;
        }
        else if (game_view.x + game_view.w-pad_x < obj_bounds.x+obj_bounds.w)
        {
            game_view.x = obj_bounds.x+obj_bounds.w+pad_x - game_view.w;
        }

        if (game_view.y + pad_y > obj_bounds.y)
        {
            game_view.y = obj_bounds.y - pad_y;
        }
        else if (game_view.y + game_view.h-pad_y < obj_bounds.y+obj_bounds.h)
        {
            game_view.y = obj_bounds.y+obj_bounds.h+pad_y - game_view.h;
        }
    }
}

bool Camera::init(int width, int height)
{
    game_view.x = 0;
    game_view.y = 0;
    game_view.w = width;
    game_view.h = height;
}

bool Camera::isInside(int x, int y)
{
    if (x > game_view.x && x < game_view.w+game_view.x && y > game_view.y && y < game_view.y + game_view.h)
    {
        return true;
    }
    return false;
}

bool Camera::isInside(SDL_Rect &obj)
{
    if (obj.x-obj.w > game_view.x && obj.x < game_view.x+game_view.w && obj.y-obj.h > game_view.y && obj.y < game_view.y + game_view.h)
    {
        return true;
    }
    return false;
}

void Camera::setPosition(int nx, int ny)
{
    game_view.x = nx;
    game_view.y = ny;

    if (follow_me)
    {
        SDL_Rect obj_bounds;
        obj_bounds = follow_me->getBounds();
        if (game_view.x + pad_x > obj_bounds.x)
        {
            game_view.x = obj_bounds.x - pad_x;
        }
        else if (game_view.x + game_view.w-pad_x < obj_bounds.x+obj_bounds.w)
        {
            game_view.x = obj_bounds.x+obj_bounds.w+pad_x - game_view.w;
        }

        if (game_view.y + pad_y > obj_bounds.y)
        {
            game_view.y = obj_bounds.y - pad_y;
        }
        else if (game_view.y + game_view.h-pad_y < obj_bounds.y+obj_bounds.h)
        {
            game_view.y = obj_bounds.y+obj_bounds.h+pad_y - game_view.h;
        }
    }
}

void Camera::setObjectBounds(int x_pad, int y_pad)
{
    pad_x = x_pad;
    pad_y = y_pad;
}

