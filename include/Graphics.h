#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include <algorithm>

#include "Log.h"
#include "Image.h"
#include "Sprite.h"
#include "Object.h"
#include "Font.h"

using namespace std;

enum DrawType
{
    DRAW_RECT = 1,
    DRAW_BOX,
    DRAW_SPRITE,
    DRAW_STRING,
    DRAW_IMAGE,
    DRAW_RAW,
    DRAW_OBJECT,
    DRAW_LINE
};

struct DrawEvent
{
    SDL_Rect r;
    int depth;
    DrawType type;

    void* asset;

    SDL_Rect clip;
    bool img_clipped;

    SDL_Color color;
    string msg;
};

#define NUM_LAYERS 5

class Graphics
{
    public:
        enum DrawLayer
        {
            LAYER_BACKGROUND = 0,
            LAYER_TILE,
            LAYER_OBJECT,
            LAYER_FOREGROUND,
            LAYER_GUI
        };

        Graphics();
        virtual ~Graphics();

        //Getters and Setters
        void setContext(SDL_Surface *val) { context = val; }
        SDL_Surface *getContext() { return context; }

        void setColor(SDL_Color new_col) { def_col = new_col; }
        void setColor (int r, int g, int b, int a=255) { def_col = (SDL_Color){r, g, b, a}; }
        SDL_Color getColor() { return def_col; }

        void setFont(Font* val) { if (val) cur_fnt = val; }
        Font* getFont() { return cur_fnt; }

        void defaultFont(Font *val) { if (val) default_fnt = val; }
        Font* defaultFont() { return default_fnt; }

        //Rendering methods

        //Primitives
        void drawRect(int x, int y, int w, int h); //Filled Rectangle
        void drawRect(SDL_Rect &r) { drawRect(r.x, r.y, r.w, r.h); }
        void drawBox(int x, int y, int w, int h, int s);  //Hollow Box
        void drawBox(SDL_Rect &r, int s) { drawBox(r.x,r.y,r.w,r.h,s); }

        void drawLine(int x1, int y1, int x2, int y2);
        void drawPolygon(int *x_pos, int *y_pos, int num_vert);

        void drawRaw(int x, int y, SDL_Surface *raw, SDL_Rect *img_clip=NULL);
        void drawString(int x, int y, string msg);
        void drawImage(int x, int y, Image *img, SDL_Rect *img_clip=NULL);
        void drawSprite(int x, int y, Sprite *spr, int f_num = -1);
        void drawObject(Object *obj);
        void drawObject(int x, int y, Object *obj);

        SDL_Surface* rawFromString(string text);

        void processScene();
        void addDrawEvent(DrawEvent *d_e) { layers[layer].push_back(d_e); }

        void setLayer(DrawLayer d) { layer = d; }
        DrawLayer getLayer() { return layer; }

    protected:
    private:
        SDL_Surface *context;
        SDL_Rect clip, pos;

        Font *cur_fnt;
        Font *default_fnt;

        SDL_Color def_col;

        vector<DrawEvent*> layers[NUM_LAYERS];
        DrawLayer layer;

        static bool compareDepth(DrawEvent *a, DrawEvent *b) { return a->depth < b->depth; }
};

#endif // GRAPHICS_H
