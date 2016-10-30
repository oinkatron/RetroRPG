#include "../include/Graphics.h"

Graphics::Graphics()
{
    context = NULL;
    cur_fnt = NULL;
    clip = (SDL_Rect){0,0,0,0};
    pos = (SDL_Rect){0, 0, 0, 0};
    def_col = {0, 0, 0, 255};

    layer = LAYER_TILE;
}

Graphics::~Graphics()
{
    //dtor
}

SDL_Surface* Graphics::rawFromString(string text)
{
    return TTF_RenderText_Blended(cur_fnt->Raw(), text.c_str(), def_col);
}

void Graphics::drawRect(int x, int y, int w, int h)
{
    clip = (SDL_Rect){x,y,w,h};

    SDL_FillRect(context, &clip, SDL_MapRGB(context->format, def_col.r, def_col.g, def_col.b));
}

void Graphics::drawBox(int x, int y, int w, int h, int s)
{
    drawRect(x - s, y - s, w + s, s);
    drawRect(x + w, y - s, s, h + s);
    drawRect(x - s, y, s, h + s);
    drawRect(x, y + h, w + s, s);
}

void Graphics::drawRaw(int x, int y, SDL_Surface *raw, SDL_Rect *img_clip)
{
    if (!context)
    {
        Log::game_log->pushError("Graphics Error: No context set!");
        return;
    }
    if (!raw)
    {
        Log::game_log->pushError("Graphics Error: Raw Image is Null! Cannot draw.");
        return;
    }
    pos.x = x;
    pos.y = y;
    pos.w = 0;
    pos.h = 0;

    SDL_BlitSurface(raw, img_clip, context, &pos);
}

void Graphics::drawImage(int x, int y, Image *img, SDL_Rect* img_clip)
{
    if (!context)
    {
        Log::game_log->pushError("Graphics Error: No context set!");
        return;
    }
    if (!img || !img->getRaw())
    {
        Log::game_log->pushError("Graphics Error: Image is Null cannot draw!");
        return;
    }

    pos.x = x;
    pos.y = y;
    pos.w = 0;
    pos.h = 0;

    SDL_BlitSurface(img->getRaw(), img_clip, context, &pos);
}

void Graphics::drawSprite(int x, int y, Sprite *spr, int f_num)
{
    if (!context)
    {
        Log::game_log->pushError("Graphics Error: No context set!");
        return;
    }
    if (!spr || !spr->Parent() || !spr->Parent()->Raw())
    {
        Log::game_log->pushError("Graphics Error: Sprite is Null, cannot draw!");
        return;
    }

    pos.x = x;
    pos.y = y;
    pos.w = 0;
    pos.h = 0;

    if (f_num >= 0 && f_num < spr->Parent()->numFrames())
        clip = spr->getFrame(f_num);
    else
        clip = spr->getNextFrame();

    SDL_BlitSurface(spr->Parent()->Raw()->getRaw(), &clip, context, &pos);
}


void Graphics::drawObject(Object *obj)
{
    if (!context)
    {
        Log::game_log->pushError("Graphics Error: No context set!");
        return;
    }

    if (!obj)
    {
        Log::game_log->pushError("Object is Null cannot draw!");
        return;
    }


    if (!obj->sprite())
    {
        clip = obj->getBounds();
        setColor(128, 0, 128);
        drawRect(clip.x, clip.y, clip.w, clip.h);
    }
    else
    {
        drawSprite((int)obj->X() - obj->xOrigin(), (int)obj->Y() - obj->yOrigin(), obj->sprite());
    }
}

void Graphics::drawString(int x, int y, string msg)
{
    SDL_Surface *raw_msg = NULL;
    if (!cur_fnt)
    {
        if (!default_fnt)
        {
           Log::game_log->pushError("Font not set! Cannot render text");
           return;
        }
        raw_msg = TTF_RenderText_Solid(default_fnt->Raw(), msg.c_str(), def_col);

    }
    else
    {
       raw_msg = TTF_RenderText_Solid(cur_fnt->Raw(), msg.c_str(), def_col);
    }

    drawRaw(x, y, raw_msg);
}

void Graphics::drawObject(int x, int y, Object *obj)
{
    if (!context)
    {
        Log::game_log->pushError("Graphics Error: No context set!");
        return;
    }

    if (!obj)
    {
        Log::game_log->pushError("Object is Null cannot draw!");
        return;
    }

    if (!obj->sprite())
    {
        setColor(128, 0, 128);
        drawRect(x, y, obj->W(), obj->H());
    }
    else
    {
        drawSprite(x, y, obj->sprite());
    }
}

void Graphics::processScene()
{
   for (int ii = 0; ii < NUM_LAYERS; ii++)
   {
       sort(layers[ii].begin(), layers[ii].end(), compareDepth);
       //Log::game_log->pushLog("Number of lines on layer 0" + toString(ii) + ": " + toString(layers[ii].size()));

       for (int i = 0; i < layers[ii].size(); i++)
       {
           //Log::game_log->pushLog("Depth: " + toString(layers[ii][i]->depth));
           switch (layers[ii][i]->type)
           {
              case DRAW_SPRITE:
              {
                 drawSprite(layers[ii][i]->r.x, layers[ii][i]->r.y, (Sprite*)layers[ii][i]->asset);
                 break;
              }
              case DRAW_IMAGE:
              {
                 if (layers[ii][i]->img_clipped)
                    drawImage(layers[ii][i]->r.x, layers[ii][i]->r.y, (Image*)layers[ii][i]->asset, &layers[ii][i]->clip);
                 else
                    drawImage(layers[ii][i]->r.x, layers[ii][i]->r.y, (Image*)layers[ii][i]->asset);
                 break;
              }
              case DRAW_RAW:
              {
                 if (layers[ii][i]->img_clipped)
                    drawRaw(layers[ii][i]->r.x, layers[ii][i]->r.y, (SDL_Surface*)layers[ii][i]->asset, &layers[ii][i]->clip);
                 else
                    drawRaw(layers[ii][i]->r.x, layers[ii][i]->r.y, (SDL_Surface*)layers[ii][i]->asset);
                 break;
              }
              case DRAW_LINE:
              {
                 setColor(layers[ii][i]->color);
                 //drawLine(layers[ii][i]->r.x, layers[ii][i]->r.y, layers[ii][i]->r.w, layers[ii][i]->r.h);
                 break;
              }
              case DRAW_RECT:
              {
                 setColor(layers[ii][i]->color);
                 drawRect(layers[ii][i]->r);
                 break;
              }
              case DRAW_BOX:
              {
                 setColor(layers[ii][i]->color);
                 drawBox(layers[ii][i]->r, layers[ii][i]->clip.x);
                 break;
              }
              case DRAW_OBJECT:
              {
                 drawObject(layers[ii][i]->r.x, layers[ii][i]->r.y, (Object*)layers[ii][i]->asset);
                 break;
              }
              case DRAW_STRING:
              {
                 setColor(layers[ii][i]->color);
                 drawString(layers[ii][i]->r.x, layers[ii][i]->r.y, layers[ii][i]->msg);
                 break;
              }
           }

           delete layers[ii][i];
       }

       layers[ii].clear();
   }
}
