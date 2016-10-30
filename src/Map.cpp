#include "../include/Map.h"

string Map::map_dir = "res/maps/";
string Map::map_exten = ".map";

Map::Map()
{
    name = "";
    draw_grid = false;

    t_sheet = NULL;
    back_offset = new PosObj();
    fore_offset = new PosObj();
    back_color = {0,0,0,255};

    width = 0;
    height = 0;
    tile_size = 0;

    back_image = NULL;
    fore_image = NULL;

    limits.x = 0;
    limits.y = 0;
    limits.w = 0;
    limits.h = 0;
}

Map::Map(string m_name)
{
    loadMap(m_name);
    draw_grid = false;
}

Map::Map(string m_name, int w, int h, int size)
{
    newMap(m_name, w, h, size);
    draw_grid = false;
}

bool Map::saveMap(string f_name)
{
    ofstream m_data, m_file;

    m_data.open((map_dir+f_name+map_exten).c_str(), ios::out| ios::trunc);
    if (!m_data.is_open())
    {
        Log::game_log->pushError("Save failed! Could not open: " + map_dir+ f_name+map_exten);
        return false;
    }

    //Create MapInfo Section
    m_data << "[MapInfo]\n";
    if (!m_data.good())
    {
        Log::game_log->pushError("Error saving map: " + f_name);
    }

    m_data << "name = " + toString(name) + "\n";
    m_data << "tile_size = " + toString(tile_size) + "\n";
    m_data <<  "width = " + toString(width) + "\n";
    m_data << "height = " + toString(height) + "\n";
    m_data << "tilesheet = " + sheet_name + "\n";

    if (!m_data.good())
    {
        Log::game_log->pushError("Error saving map: " + f_name);
        return false;
    }

    m_data.close();

    m_file.open((map_dir+f_name+".dat").c_str(), ios::binary | ios::trunc);
    if (!m_file.is_open())
    {
        Log::game_log->pushError("Error saving map data: " + f_name);
        return false;
    }

    for (int i = 0; i < tiles.size(); i++)
    {
        m_file << toString(tiles[i]->id) << " " << toString(tiles[i]->type) << " ";
        if (!m_file.good())
        {
            Log::game_log->pushError("Error saving map data: " + f_name);
            m_file.close();
            return false;
        }

    }

    m_file.close();

    return true;

}

bool Map::loadMap(string f_name)
{
    DataFile m_file;
    ifstream m_data;

    string map_name;
    string b_img_n;
    string f_img_n;

    float b_img_off_x;
    float b_img_off_y;
    float f_img_off_x;
    float f_img_off_y;

    int map_w, map_h, t_size;

    if (!m_file.loadFile(map_dir+f_name+map_exten))
    {
        Log::game_log->pushError("Unable to load map: " + f_name);
        return false;
    }

    file_name = f_name;

    if (m_file.numSections() < 1)
    {
        Log::game_log->pushError(toString(m_file.numSections()) + " Invalid Map file: " + f_name);
        return false;
    }
    else
    {
        if (m_file.getSectionName(0) != "MapInfo")
        {
            Log::game_log->pushError("No MapInfo section found: " + f_name);
            return false;
        }
    }

    if (!m_file.getMember<string>("MapInfo", "name", &map_name))
    {
        Log::game_log->pushLog("No name specified setting name to file name");
        map_name = f_name;
    }

    if (!m_file.getMember<string>("MapInfo", "background_image", &b_img_n))
    {
        Log::game_log->pushLog("No background image specified!");
        b_img_n = "";
    }

    if (!m_file.getMember<string>("MapInfo", "foreground_image", &f_img_n))
    {
        Log::game_log->pushLog("No foreground image specified!");
        f_img_n = "";
    }

    if (!m_file.getMember<float>("MapInfo", "background_image_offset_x", &b_img_off_x))
    {
        Log::game_log->pushLog("No background X offset specified....assuming 0!");
        b_img_off_x = 0;
    }

    if (!m_file.getMember<float>("MapInfo", "background_image_offset_y", &b_img_off_y))
    {
        Log::game_log->pushLog("No background Y offset specified....assuming 0!");
        b_img_off_y = 0;
    }

    if (!m_file.getMember<float>("MapInfo", "foreground_image_offset_x", &f_img_off_x))
    {
        Log::game_log->pushLog("No foreground X offset specified....assuming 0!");
        f_img_off_x = 0;
    }

    if (!m_file.getMember<float>("MapInfo", "foreground_image_offset_y", &f_img_off_y))
    {
        Log::game_log->pushLog("No foreground Y offset specified....assuming 0!");
        f_img_off_y = 0;
    }

    if (!m_file.getMember<int>("MapInfo", "tile_size", &t_size))
    {
        Log::game_log->pushError("Unable to find tile_size in map header... assuming 32");
        t_size = 32;
    }

    if (!m_file.getMember<int>("MapInfo", "width", &map_w))
    {
        Log::game_log->pushError("Unable to find width in map header");
        width = 0;
    }

    if (!m_file.getMember<int>("MapInfo", "height", &map_h))
    {
        Log::game_log->pushError("Unable to find height in map header");
        height = 0;
    }

    if (!m_file.getMember<string>("MapInfo", "tilesheet", &sheet_name))
    {
        Log::game_log->pushError("No tilesheet specified...using color codes");
        t_sheet = NULL;
    }
    else
    {
       if (!(t_sheet = (Tilesheet*)Asset::get(sheet_name)))
       {
            Log::game_log->pushError("Cannot find tilesheet...using color codes");
       }
    }

    newMap(map_name, map_w, map_h, t_size); //making blank map

    if (b_img_n != "")
    {
        Image::onLoad(b_img_n);
        back_image = dynamic_cast<Image*>(Asset::get(b_img_n));
    }
    if (f_img_n != "")
    {
        Image::onLoad(f_img_n);
        fore_image = dynamic_cast<Image*>(Asset::get(f_img_n));
    }

    backgroundOffset(b_img_off_x, b_img_off_y);
    foregroundOffset(f_img_off_x, f_img_off_y);

    m_data.open((map_dir+f_name+".dat").c_str(), ios::binary);
    if (!m_data.is_open())
    {
        Log::game_log->pushError("Map Datafile not found..Generating blank map");
        return true;
    }

    int tmp_type;

    for (int i = 0; i < width*height; i++)
    {

        if (!(m_data >> tiles[i]->id))
        {
            Log::game_log->pushError("Error reading map data!!");
            m_data.close();
            break;
        }

        if (!(m_data >> tmp_type))
        {
            Log::game_log->pushError("Error reading map data!");
            m_data.close();
            break;
        }
        tiles[i]->type = (TileType)tmp_type;
    }

    if (tiles.size() != width*height)
    {
        Log::game_log->pushError("Discretion in map size!");
        tiles.clear();
        return false;
    }

    limits.x = 0;
    limits.y = 0;
    limits.w = width*tile_size;
    limits.h = height*tile_size;

    return true;
}

SDL_Rect& Map::tileBounds(int x, int y)
{
    t_rect.x = x*tile_size;
    t_rect.y = y*tile_size;
    t_rect.w = tile_size;
    t_rect.h = tile_size;

    return t_rect;
}

SDL_Rect Map::backgroundClip(SDL_Rect &cam_clip, PosObj* cam_obj_pos)
{
    SDL_Rect ret = {0, 0, 0, 0};

    if (!back_image)
    {
        Log::game_log->pushError("No background image set cannot grab clip!");
        return ret;
    }

    if (back_image->W() <= cam_clip.w)
    {
        ret.x = 0;
        ret.w = back_image->W();
    }
    else if (back_image->W() > cam_clip.w)
    {
        if (cam_obj_pos)
            ret.x = (cam_obj_pos->X()/(float)(tile_size*width))*(back_image->W()-cam_clip.w);
        else
            ret.x = ((float)cam_clip.x/(float)(tile_size*width))*back_image->W();

        ret.w = cam_clip.w;

        if (ret.x < 0)
        {
            ret.x = 0;
        }
        else if (ret.x + cam_clip.w > back_image->W())
        {
            ret.x = back_image->W()-cam_clip.w;
        }
    }

    if (back_image->H() <= cam_clip.h)
    {
        ret.y = 0;
        ret.h = back_image->H();
    }
    else if (back_image->H() > cam_clip.h)
    {
        if (cam_obj_pos)
        {
            ret.y = (cam_obj_pos->Y()/(float)(tile_size*height))*(back_image->H()-cam_clip.h);
        }
        else
        {
            ret.y = ((float)cam_clip.y/(float)(tile_size*height))*back_image->H();
        }

        ret.h = cam_clip.h;

        if (ret.y < 0)
        {
            ret.y = 0;
        }
        else if (ret.y + cam_clip.h > back_image->H())
        {
            ret.y = back_image->H()-cam_clip.h;
        }
    }

    return ret;
}

SDL_Rect Map::foregroundClip(SDL_Rect &cam_clip, PosObj* cam_obj_pos)
{
    SDL_Rect ret = {0, 0, 0, 0};

    if (!fore_image)
    {
        Log::game_log->pushError("No foreground image set cannot grab clip!");
        return ret;
    }

    if (fore_image->W() <= cam_clip.w)
    {
        ret.x = 0;
        ret.w = fore_image->W();
    }
    else if (fore_image->W() > cam_clip.w)
    {
        if (cam_obj_pos)
            ret.x = (cam_obj_pos->X()/(float)(tile_size*width))*(fore_image->W()-cam_clip.w);
        else
            ret.x = ((float)cam_clip.x/(float)(tile_size*width))*fore_image->W();

        ret.w = cam_clip.w;

        if (ret.x < 0)
        {
            ret.x = 0;
        }
        else if (ret.x + cam_clip.w > fore_image->W())
        {
            ret.x = fore_image->W()-cam_clip.w;
        }
    }

    if (fore_image->H() <= cam_clip.h)
    {
        ret.y = 0;
        ret.h = fore_image->H();
    }
    else if (fore_image->H() > cam_clip.h)
    {
        if (cam_obj_pos)
        {
            ret.y = (cam_obj_pos->Y()/(float)(tile_size*height))*(fore_image->H()-cam_clip.h);
        }
        else
        {
            ret.y = ((float)cam_clip.y/(float)(tile_size*height))*fore_image->H();
        }

        ret.h = cam_clip.h;

        if (ret.y < 0)
        {
            ret.y = 0;
        }
        else if (ret.y + cam_clip.h > fore_image->H())
        {
            ret.y = back_image->H()-cam_clip.h;
        }
    }

    return ret;
}

bool Map::isInside(int x, int y)
{
    if (x > 0 && x < width*tile_size && y > 0 && y < height*tile_size)
    {
        return true;
    }
    return false;
}

bool Map::isInside(SDL_Rect &obj)
{
    if (obj.x-obj.w > 0 && obj.x < width*tile_size && obj.y-obj.h > 0 && obj.y < height*tile_size)
    {
        return true;
    }
    return false;
}

void Map::newMap(string n_name, int w, int h, int size)
{
    tiles.clear();

    name = n_name;

    width = w;
    height = h;

    tile_size = size;

    back_image = NULL;

    limits.x = 0;
    limits.y = 0;
    limits.w = w*tile_size;
    limits.h = h*tile_size;

    Tile *tmp;

    while (tiles.size() < w*h)
    {
        tmp = new Tile;
        tmp->id = 0;
        tmp->type = TILE_BLANK;

        tiles.push_back(tmp);
    }
}

Map::~Map()
{
    tiles.clear();
    if (t_sheet)
        delete t_sheet;
}
