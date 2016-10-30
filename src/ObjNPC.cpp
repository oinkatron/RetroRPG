#include "../include/ObjNPC.h"

ObjNPC::~ObjNPC()
{
    //dtor
}

void ObjNPC::handleKeyInput(SDLKey key, bool pressed)
{
    ControlScheme controls = Controls();
    if (key == controls.upKey())
    {
        if (pressed)
        {
            Velocity().y = -25;
            Velocity().x = 0;
            sprite(spr_set.w_u_spr);
            cur_dir = DIR_UP;
            moving = true;
        }
        else
        {
            if (cur_dir == DIR_UP)
            {
                moving = false;
                Velocity().y = 0;
                sprite(spr_set.u_spr);
            }
        }
    }
    else if (key == controls.downKey())
    {
        if (pressed)
        {
            Velocity().y = 25;
            Velocity().x = 0;
            sprite(spr_set.w_d_spr);
            cur_dir = DIR_DOWN;
            moving = true;
        }
        else
        {
            if (cur_dir == DIR_DOWN)
            {
                moving = false;
                Velocity().y = 0;
                sprite(spr_set.d_spr);
            }
        }
    }
    else if ( key == controls.rightKey())
    {
        if (pressed)
        {
            Velocity().y = 0;
            Velocity().x = 25;
            sprite(spr_set.w_r_spr);
            cur_dir = DIR_RIGHT;
            moving = true;
        }
        else
        {
            if (cur_dir == DIR_RIGHT)
            {
                moving = false;
                Velocity().x = 0;
                sprite(spr_set.r_spr);
            }
        }
    }
    else if ( key == controls.leftKey())
    {
        if (pressed)
        {
            Velocity().y = 0;
            Velocity().x = -25;
            sprite(spr_set.w_l_spr);
            cur_dir = DIR_LEFT;
            moving = true;
        }
        else
        {
            if (cur_dir == DIR_LEFT)
            {
                moving = false;
                Velocity().x = 0;
                sprite(spr_set.l_spr);
            }
        }
    }
}

void ObjNPC::onLoop()
{
    if (ch_dir)
    {

        ch_dir = false;
        switch (cur_dir)
        {
            case DIR_UP:
                Velocity().y = -25;
                Velocity().x = 0;
                sprite(spr_set.w_u_spr);
                break;
            case DIR_DOWN:
                Velocity().y = 25;
                Velocity().x = 0;
                sprite(spr_set.w_d_spr);
                break;
            case DIR_LEFT:
                Velocity().x = -25;
                Velocity().y = 0;
                sprite(spr_set.w_l_spr);
                break;
            case DIR_RIGHT:
                Velocity().x = 25;
                Velocity().y = 0;
                sprite(spr_set.w_r_spr);
                break;
        }
    }
    else
    {
        if (moving)
        {
            onMove();
        }
    }
}
