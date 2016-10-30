#ifndef IMAGE_H
#define IMAGE_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <string>
#include <map>

#include "Log.h"
#include "Asset.h"

using namespace std;

class Image : public Asset
{
    public:
        Image() : Asset()
        {
            raw = NULL;
        }
        Image(string filename) : Asset (filename)
        {
            raw = NULL;
        }

        virtual ~Image();

        static bool onLoad(string f_name);
        static string img_path;

        int W() { return raw->w; }
        int H() { return raw->h; }

        //Getters & Setters
        SDL_Surface *getRaw() { return raw; }
        void setRaw (SDL_Surface *val) { raw = val; }
        void setRaw(string filename);

        //Public vars
        static string path;

    protected:
    private:
        SDL_Surface *raw;
};

#endif // IMAGE_H
