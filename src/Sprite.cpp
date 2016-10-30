#include "../include/Sprite.h"

string SpriteBase::dir = "res/sprites/";
string SpriteBase::exten = ".spr";

SpriteBase::SpriteBase()
{
    Name("Sprite_" + toString(uID()));
    sheet = NULL;
    frames = NULL;

    start_frame_x = 0;
    start_frame_y = 0;

    def_anim_ticks = 0;

    num_frames = 0;
    horizontal = false;
}

SpriteBase::~SpriteBase()
{
    delete [] frames;
}

void SpriteBase::initFrames()
{
    frames = new SDL_Rect[num_frames];

    for (int i = 0; i < num_frames; i++)
    {
        frames[i].x = (start_frame_x+i)*frame_width;
        frames[i].y = start_frame_y*frame_height;
        frames[i].w = frame_width;
        frames[i].h = frame_height;
    }
}

bool SpriteBase::onLoad(string filename)
{
    DataFile spr_data;

    //tmp sprite data
    string spr_name;
    string image_name;
    int num_fr;
    int s_x;
    int s_y;
    int s_w;
    int s_h;
    int anim_sp;

    if (!spr_data.loadFile(dir+filename+exten))
    {
        Log::game_log->pushError("Unable to load Sprite: " + filename);
        return false;
    }

    for (int i = 0; i < spr_data.numSections(); i++)
    {
        if (spr_data.getSectionName(i) == "Sprite")
        {
            if (!spr_data.getMember(i, "image_name", &image_name))
            {
                Log::game_log->pushError("No image specified...cannot load sprite");
                continue;
            }

            if (!spr_data.getMember(i, "name", &spr_name))
            {
                spr_name == "";
            }

            if (!spr_data.getMember(i, "num_frames", &num_fr))
            {
                num_fr = 1;
            }

            if (!spr_data.getMember(i, "start_x", &s_x))
            {
                s_x = 0;
            }

            if (!spr_data.getMember(i, "start_y", &s_y))
            {
                s_y = 0;
            }

            if (!spr_data.getMember(i, "frame_width", &s_w))
            {
                s_w = 32;
            }

            if (!spr_data.getMember(i, "frame_height", &s_h))
            {
                s_h = 32;
            }

            if (!spr_data.getMember(i, "animation_speed", &anim_sp))
            {
                anim_sp = 100;
            }

            if (Asset::get(spr_name))
            {
                Log::game_log->pushError("Asset: " + spr_name + "alreadt exists!");
                continue;
            }

            SpriteBase *new_spr = new SpriteBase();

            new_spr->numFrames(num_fr);
            new_spr->startX(s_x);
            new_spr->startY(s_y);
            new_spr->frameWidth(s_w);
            new_spr->frameHeight(s_h);
            new_spr->defaultAnimationSpeed(anim_sp);
            new_spr->Raw(image_name);

            if (spr_name != "")
                new_spr->Name(spr_name);

            new_spr->initFrames();

            Asset::add(new_spr);
        }
    }
}

Sprite::Sprite(SpriteBase* sp)
{
    parent = sp;
    start_ticks = SDL_GetTicks();

    if (sp)
        anim_ticks = sp->defaultAnimationSpeed();

    cur_frame = 0;
}

Sprite::Sprite(string spr_b_name)
{
    parent = (SpriteBase*)Asset::get(spr_b_name);
    start_ticks = SDL_GetTicks();

    if (parent)
        anim_ticks = parent->defaultAnimationSpeed();

    cur_frame = 0;

}

Sprite::~Sprite()
{

}


SDL_Rect Sprite::getFrame(int frame_num)
{
    if (!parent)
    {
        Log::game_log->pushError("Corrupted Sprite!");
        return (SDL_Rect){0, 0, 0, 0};
    }


    if (frame_num >= 0 && frame_num < parent->numFrames())
    {
        return parent->Frames()[frame_num];
    }
    else
    {
        return (SDL_Rect){0, 0, 0, 0};
    }
}

SDL_Rect Sprite::getNextFrame()
{
    if (!parent)
    {
        Log::game_log->pushError("Corrupted Sprite!");
        return (SDL_Rect){0, 0, 0, 0};
    }

    if (SDL_GetTicks() - start_ticks > (anim_ticks/Timer::fps.getGameSpeed()))
    {
        start_ticks = SDL_GetTicks();

        cur_frame++;
        if (cur_frame >= parent->numFrames())
        {
            cur_frame = 0;
        }
    }

    return parent->Frames()[cur_frame];
}
