#ifndef MAP_H
#define MAP_H

#include <string>
#include <fstream>

#include "Log.h"
#include "DataFile.h"
#include "Tilesheet.h"
#include "PosObj.h"

using namespace std;

enum TileType
{
    TILE_NULL = -1,
    TILE_BLANK = 0,
    TILE_SOLID = 1
};

struct Tile
{
    TileType type;
    int id;
};

class Map
{
    public:
        Map();
        Map(string m_name);
        Map(string m_name, int w, int h, int size);

        static void setMapDir(string val) { map_dir = val; }

        bool loadMap(string f_name);
        bool saveMap(string f_name);
        void newMap(string name, int w, int h, int size);

        SDL_Rect& tileBounds(int x, int y);
        Tile* getTile(int x, int y) { return getTile((y*width)+x); }
        Tile* getTile(int val) { if (val >= tiles.size() || val < 0) return NULL; else return tiles[val]; }

        bool isInside(int x, int y);
        bool isInside(SDL_Rect &obj);

        void tileType(int x, int y, TileType t) { getTile(x, y)->type = t; }
        TileType tileType(int x, int y) { return getTile(x, y)->type; }

        void tileID(int x, int y, int id) { getTile(x, y)->id = id; }
        int tileID(int x, int y) { return getTile(x, y)->id; }

        Tilesheet* tileSheet() { return t_sheet; }
        void tileSheet(Tilesheet* val) { t_sheet = val; }
        void tileSheet(string t_name) { t_sheet = (Tilesheet*)Asset::get(t_name); }

        int mapWidth() { return width; }
        int mapHeight() { return height; }

        int Width() { return width*tile_size; }
        int Height() { return height*tile_size; }

        int tileSize() { return tile_size; }

        int getXLimit() { return limits.w; }
        int getYLimit() { return limits.h; }

        int getNumTiles() { return tiles.size(); }

        void drawGrid(bool val) { draw_grid = val; }
        bool drawGrid() { return draw_grid; }

        string Name() { return name; }
        void Name(string val) { name = val; }

        string fileName() { return file_name; }
        void fileName(string val) { file_name = val; }

        Image* backgroundImage() { return back_image; }
        void backgroundImage(Image *val) { back_image = val; }
        void backgroundImage(string i_name) { back_image = dynamic_cast<Image*>(Asset::get(i_name)); }

        void backgroundOffset(float nx, float ny) { back_offset->X(nx); back_offset->Y(ny); }
        PosObj* backgroundOffset() { return back_offset; }

        SDL_Rect backgroundClip(SDL_Rect &cam_clip, PosObj *cam_obj_pos=NULL);

        Image* foregroundImage() { return fore_image; }
        void foregroundImage(Image *val) { fore_image = val; }
        void foregroundImage(string i_name) { fore_image = dynamic_cast<Image*>(Asset::get(i_name)); }

        void foregroundOffset(float nx, float ny) { fore_offset->X(nx); fore_offset->Y(ny); }
        PosObj *foregroundOffset() { return fore_offset; }

        SDL_Rect foregroundClip(SDL_Rect &cam_clip, PosObj *cam_obj_pos=NULL);

        SDL_Color backgroundColor() { return back_color; }
        void backgroundColor(SDL_Color val) { back_color = val; }
        void backgroundColor (int r, int g, int b, int a=255) { back_color = {r,g,b,a}; }

        void gravityLevel(float val) { grav_level = val; }
        float gravityLevel() { return grav_level; }

        void frictionLevel(float val) { fric_level = val;}
        float frictionLevel() { return fric_level; }

        virtual ~Map();
    protected:
    private:
        static string map_dir;
        static string map_exten;

        SDL_Rect limits;
        SDL_Rect t_rect;

        float grav_level;
        float fric_level;

        Tilesheet *t_sheet;
        string sheet_name;

        string name;
        string file_name;
        vector<Tile*> tiles;

        Image* back_image;
        PosObj *back_offset;
        SDL_Color back_color;

        Image* fore_image;
        PosObj *fore_offset;

        int width;
        int height;

        int tile_size;

        bool draw_grid;
};

#endif // MAP_H
