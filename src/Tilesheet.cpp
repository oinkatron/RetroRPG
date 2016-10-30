#include "../include/Tilesheet.h"

string Tilesheet::tilesheet_dir = "res/tilesheets/";
string Tilesheet::tilesheet_exten = ".sht";

SDL_Rect Tilesheet::getClip(int id)
{
    if (id > num_x * num_y || id < 0)
    {
        Log::game_log->pushError("Tile Id: " + toString(id) + " is out of scope");
        rect = {0, 0, 0, 0};
        return rect;
    }
    int x = id%num_x;
    int y = id/num_x;

    rect.x = x * (tile_width+gap_x);
    rect.y = y * (tile_height+gap_y);
    rect.w = tile_width;
    rect.h = tile_height;

    return rect;
}

SDL_Rect Tilesheet::getClip(int x, int y)
{
    if (x > num_x || x < 0 || y > num_y || y < 0)
    {
        Log::game_log->pushError("Tile Location (X: " + toString(x) + ", Y: " + toString(y) + ") is out of scope");
        rect = {0, 0, 0, 0};
        return rect;
    }
    rect.x = x * (tile_width+gap_x);
    rect.y = y * (tile_height+gap_y);
    rect.w = tile_width;
    rect.h = tile_height;

    return rect;
}

bool Tilesheet::onLoad(string f_name)
{
    DataFile file;

    string t_name ="";
    string i_name = "";
    int t_width = 0;
    int t_height = 0;
    int t_gx = 0;
    int t_gy = 0;

    if (!file.loadFile(tilesheet_dir+f_name+tilesheet_exten))
    {
        Log::game_log->pushError("Cannot find tilesheet: " + f_name);
        return false;
    }

    for (int i = 0; i < file.numSections(); i++)
    {
        if (file.getSectionName(i) == "Tilesheet")
        {
            if (!file.getMember(i, "image_name", &i_name))
            {
                Log::game_log->pushError("Tilesheet image name not set cannot create tile sheet!");
                continue;
            }
            if (!file.getMember(i, "name", &t_name))
            {
                Log::game_log->pushError("Cannot find Tilesheet member: name, using default");
            }

            if (!file.getMember(i, "tile_width", &t_width))
            {
                Log::game_log->pushError("Cannot find Tilesheet member: tile_width, using default");
                t_width = 32;
            }

            if (!file.getMember(i, "tile_height", &t_height))
            {
                Log::game_log->pushError("Cannot find Tilesheet member: tile_height, using default");
                t_height = 32;
            }

            if (!file.getMember(i, "gap_x", &t_gx))
            {
                Log::game_log->pushError("Cannot find Tilesheet member: gap_x, using default");
                t_gx = 0;
            }

            if (!file.getMember(i, "gap_y", &t_gy))
            {
                Log::game_log->pushError("Cannot find Tilesheet member: gap_y, using default");
                t_gy = 0;
            }

            Tilesheet * t = (t_name == "") ? new Tilesheet() : new Tilesheet(t_name);
            t->tileWidth(t_width);
            t->tileHeight(t_height);
            t->gapX(t_gx);
            t->gapY(t_gy);
            Image::onLoad(i_name);
            t->Raw((Image*)Asset::get(i_name));
            t->numX(t->Raw()->W()/t_width);
            t->numY(t->Raw()->H()/t_height);

            Asset::add(t);
        }
    }

    return true;
}

Tilesheet::~Tilesheet()
{

}
