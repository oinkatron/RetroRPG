#ifndef FONT_H
#define FONT_H

#include <string>
#include <vector>
#include <SDL/SDL_ttf.h>

#include "Log.h"
#include "Asset.h"

using namespace std;

class Font : public Asset
{
    public:
        Font()
        {
            fnt = NULL;
            size = 0;
        }
        Font(string fname) : Asset(fname)
        {
            fnt = NULL;
            size = 0;
        }

        virtual ~Font();

        static string font_path;
        static string font_exten;
        static bool onLoad(string f_name);

        //Getters and Setters
        int Size() { return size; }
        void Size(int val) { size = val; }
        TTF_Font* Raw() { return fnt; }
        void Raw(TTF_Font* val) { if (fnt) TTF_CloseFont(fnt); fnt = val; }

    protected:
    private:
        TTF_Font *fnt;
        int size;

};

#endif // FONT_H
