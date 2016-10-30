#include "../include/Image.h"

string Image::img_path = "res/images/";

bool Image::onLoad(string f_name)
{
    if (Asset::get(f_name))
    {
        Log::game_log->pushLog("Asset with name: " + f_name + " already loaded!");
        return false;
    }

    Image *tmp_img = new Image(f_name);
    SDL_Surface *tmp, *opt;

    f_name = img_path + f_name;
    tmp = IMG_Load(f_name.c_str());
    if (!tmp)
    {
        Log::game_log->pushError("Image: " + f_name + " not found");
        return false;
    }

    opt = SDL_DisplayFormat(tmp);
    if (!opt)
    {
        Log::game_log->pushError("Could not optimize Image!");
        SDL_FreeSurface(tmp);

        return false;
    }

    SDL_SetColorKey(opt, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(opt->format, 255, 0, 255));
    tmp_img->setRaw(opt);
    SDL_FreeSurface(tmp);

    add(tmp_img);

    return true;
}


Image::~Image()
{
    SDL_FreeSurface(raw);
}
