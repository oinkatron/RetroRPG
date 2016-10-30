#ifndef TILESHEET_H
#define TILESHEET_H

#include <string>

#include "Log.h"
#include "DataFile.h"
#include "Asset.h"
#include "Image.h"

class Tilesheet : public Asset
{
    public:
        Tilesheet() : Asset()
        {
            num_x = num_y = 0;
            gap_x = gap_y = 0;
        }
        Tilesheet(string f_name) : Asset(f_name)
        {
            num_x = num_y = 0;
            gap_x = gap_y = 0;
        }

        virtual ~Tilesheet();

        SDL_Rect getClip(int id);
        SDL_Rect getClip(int x, int y);

        static string tilesheet_dir;
        static string tilesheet_exten;

        static bool onLoad(string f_name);

        Image* Raw() { return tilesheet; }
        void Raw(Image * v) { tilesheet = v;}

        void tileWidth(int w) { tile_width = w; }
        int tileWidth() { return tile_width; }

        void tileHeight(int h) { tile_height = h;}
        int tileHeight() { return tile_height; }

        void numX(int v) { num_x = v; }
        int numX() { return num_x; }

        void numY(int v) { num_y = v; }
        int  numY() { return num_y; }

        void gapX(int v) { gap_x = v; }
        int gapX() { return gap_x; }

        void gapY(int v) { gap_y = v; }
        int gapY() { return gap_y; }

    protected:
    private:
        Image* tilesheet;
        SDL_Rect rect;

        int tile_width;
        int tile_height;

        int num_x, num_y;

        int gap_x;
        int gap_y;
};

#endif // TILESHEET_H
