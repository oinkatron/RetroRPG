#ifndef PANEL_H
#define PANEL_H

#include <iostream>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <string>
#include <vector>

#include "Log.h"
#include "Font.h"
#include "Graphics.h"
#include "PosObj.h"
#include "GameEvent.h"

using namespace std;

class Panel
{
    public:
        Panel();
        virtual ~Panel();

        static int panel_id_num;
        static Panel* focused_panel;
        static Panel* sel_panel;
        static Panel* hovered_panel;
        static vector<Panel*> panel_bank;
        static void addWindow(Panel* p) { panel_bank.push_back(p); }
        static void flush();

        virtual void onKeyPress(SDLKey key, bool shift);
        virtual void onClick(PosObj &m_coords);
        virtual void onRelease(PosObj &m_coords);
        virtual void onFocus();
        virtual void onUnfocus();
        virtual void onEnter(PosObj &m_coords);
        virtual void onExit();
        virtual void onHover(PosObj &m_coords);
        virtual void onLoop();
        virtual void onDraw(Graphics &g);

        Panel *getClickedPanel(PosObj &m_coors);

        void addChild(Panel* p);

        bool isInside(int mx, int my);
        bool isInside(SDL_Rect &r);

        void setPosition(float n_x, float n_y) { pos.X(n_x); pos.Y(n_y); dimen.x = (int)pos.X(); dimen.y = (int)pos.Y(); }
        void X(float val) { pos.X(val); dimen.x = (int)pos.X(); }
        void Y(float val) { pos.Y(val); dimen.y = (int)pos.Y(); }
        PosObj* getPosition() { return &pos; }
        float X() { return pos.X(); }
        float Y() { return pos.Y(); }
        int screenX() { return (parent_panel) ? (int)(pos.X() + parent_panel->X()) : (int)(pos.X()); }
        int screenY() { return (parent_panel) ? (int)(pos.Y() + parent_panel->Y()) : (int)(pos.Y()); }

        void setDimensions(int n_w, int n_h) { dimen.w = n_w; dimen.h = n_h; }
        void W(int val) { dimen.w = val; }
        void H(int val) { dimen.h = val; }
        int W() { return dimen.w; }
        int H() { return dimen.h; }

        SDL_Surface *textSrf() { return text_srf; }

        void borderWidth(int val) { b_width = val; }
        int borderWidth() { return b_width; }

        int getTypeId() { return panel_id_num; }

        bool isHidden() { return hidden; }
        void Hidden(bool val) { hidden = val; }

        bool showBorder() { return show_border; }
        void showBorder(bool val) { show_border = val; }

        Panel* parentPanel() { return parent_panel; }

        void Text(string s) { text = s; updateText(); }
        string Text() { return text; }

        void textColor(int r, int g, int b, int a=255) { textOffColor(r,g,b,a); textOnColor(r,g,b,a); textPressedColor(r,g,b,a); t_on_set = true; t_off_set = true; }
        void textColor(SDL_Color &col) { textOffColor(col); textOnColor(col); textPressedColor(col); }

        void textOffColor(int r, int g, int b, int a=255) { text_off_color = (SDL_Color){r, g, b, a}; if (!mouse_inside) updateText(); t_off_set = true; }
        void textOffColor(SDL_Color &col) { text_off_color = col; if (!mouse_inside) updateText(); t_off_set = true;}
        SDL_Color &textOffColor() { return text_off_color; }

        void textOnColor(int r, int g, int b, int a=255) { text_on_color = (SDL_Color){r, g, b, a}; if (mouse_inside) updateText(); t_on_set = true; }
        void textOnColor(SDL_Color &col) { text_on_color = col; if (mouse_inside) updateText(); t_on_set = true; }
        SDL_Color &textOnColor() { return text_on_color; }

        void textPressedColor(int r, int g, int b, int a=255) { text_pressed_color = (SDL_Color){r, g, b, a}; updateText(); t_pressed_set = true; }
        void textPressedColor(SDL_Color &col) { text_pressed_color = col; updateText(); t_pressed_set = true; }
        SDL_Color &textPressedColor() { return text_pressed_color; }

        void backColor(int r, int g, int b, int a=255) { backOffColor(r,g,b,a); backOnColor(r,g,b,a); backPressedColor(r,g,b,a); bg_off_set = true; bg_on_set = true; }
        void backColor(SDL_Color &col) { backOffColor(col); backOnColor(col); backPressedColor(col); bg_on_set = true; bg_off_set = true; }

        void backOffColor(int r, int g, int b, int a=255) { back_off_color = (SDL_Color){r, g, b, a}; bg_off_set = true;}
        void backOffColor(SDL_Color &col) { back_off_color = col; bg_off_set = true; }
        SDL_Color &backOffColor() { return back_off_color; }

        void backOnColor(int r, int g, int b, int a=255) { back_on_color = (SDL_Color){r, g, b, a}; bg_on_set = true;}
        void backOnColor(SDL_Color &col) { back_on_color = col; bg_on_set = true;}
        SDL_Color &backOnColor() { return back_on_color; }

        void backPressedColor(int r, int g, int b, int a=255) { back_pressed_color = (SDL_Color){r, g, b, a}; bg_pressed_set = true; }
        void backPressedColor(SDL_Color &col) { back_pressed_color = col; bg_pressed_set = true; }
        SDL_Color &backPressedColor() { return back_pressed_color; }

        void borderColor(int r, int g, int b, int a=255) { border_color = (SDL_Color) {r, g, b, a}; b_col_set = true; }
        void borderColor(SDL_Color &col) { border_color = col; b_col_set = true; }
        SDL_Color &borderColor() { return border_color; }

        void textFont(Font* f) { fnt = f; updateText(); }
        void textFont(string f_n) { fnt = (Font*)Asset::get(f_n); updateText(); }
        Font* textFont() { return fnt; }

        void backgroundImage(Image *i) { background_image = i; if (background_image) back_image = true; }
        void backgroundImage(string i_name) { background_image = (Image*)Asset::get(i_name); if (background_image) back_image = true; }
        Image* backgroundImage() { return background_image; }

        void backImageClip(int x, int y, int w, int h) { back_clip = (SDL_Rect){x,y,w,h}; b_clip_set = true; }
        void backImageClip(SDL_Rect &val) { back_clip = (SDL_Rect){val.x,val.y,val.w,val.h}; b_clip_set = true; }
        SDL_Rect backImageClip() { return back_clip; }

        void showBackground(bool val) { show_background = val; }
        bool showBackground() { return show_background; }

        bool isSelected() { return selected; }
        int getOffX() { return (int)sel_off.x; }
        int getOffY() { return (int)sel_off.y; }

        bool isEntered() { return mouse_inside; }
        void isEntered(bool val) { mouse_inside = val; }

        bool isPressed() { return clicked; }
        void isPressed(bool val) { clicked = val; }

        void tooltipText(string val) { tooltip_text = val; }
        string tooltipText() { return tooltip_text; }

        //Panel defaults
        static void defaultBackgroundOnColor(SDL_Color c) { default_bg_on_color = c; }
        static void defaultBackgroundOnColor(int r, int g, int b, int a=255) { default_bg_on_color = (SDL_Color){r,g,b,a}; }
        static SDL_Color defaultBackgroundOnColor() { return default_bg_on_color; }

        static void defaultForegroundOnColor(SDL_Color c) { default_fg_on_color = c; }
        static void defaultForegroundOnColor(int r, int g, int b, int a=255) { default_fg_on_color = (SDL_Color){r,g,b,a}; }
        static SDL_Color defaultForegroundOnColor() { return default_fg_on_color; }

        static void defaultTextOnColor(SDL_Color c) { default_text_on_color = c; }
        static void defaultTextOnColor(int r, int g, int b, int a=255) { default_text_on_color = (SDL_Color){r,g,b,a}; }
        static SDL_Color defaultTextOnColor() { return default_text_on_color; }

        static void defaultBackgroundOffColor(SDL_Color c) { default_bg_off_color = c; }
        static void defaultBackgroundOffColor(int r, int g, int b, int a=255) { default_bg_off_color = (SDL_Color){r,g,b,a}; }
        static SDL_Color defaultBackgroundOffColor() { return default_bg_off_color; }

        static void defaultBackgroundPressedColor(SDL_Color c) { default_bg_pressed_color = c; }
        static void defaultBackgroundPressedColor(int r, int g, int b, int a=255) { default_bg_pressed_color = (SDL_Color){r,g,b,a}; }
        static SDL_Color defaultBackgroundPressedColor() { return default_bg_pressed_color; }

        static void defaultForegroundOffColor(SDL_Color c) { default_fg_off_color = c; }
        static void defaultForegroundOffColor(int r, int g, int b, int a=255) { default_fg_off_color = (SDL_Color){r,g,b,a}; }
        static SDL_Color defaultForegroundOffColor() { return default_fg_off_color; }

        static void defaultForegroundPressedColor(SDL_Color c) { default_fg_pressed_color.r = c.r; default_fg_pressed_color.g = c.g; default_fg_pressed_color.b = c.b; }
        static void defaultForegroundPressedColor(int r, int g, int b, int a=255) { default_fg_pressed_color = (SDL_Color){r,g,b,a}; }
        static SDL_Color& defaultForegroundPressedColor() { return default_fg_pressed_color; }

        static void defaultTextOffColor(SDL_Color c) { default_text_off_color = c; }
        static void defaultTextOffColor(int r, int g, int b, int a=255) { default_text_off_color = (SDL_Color){r,g,b,a}; }
        static SDL_Color defaultTextOffColor() { return default_text_off_color; }

        static void defaultTextPressedColor(SDL_Color c) { default_text_off_color = c; }
        static void defaultTextPressedColor(int r, int g, int b, int a=255) { default_text_pressed_color = (SDL_Color){r,g,b,a}; }
        static SDL_Color defaultTextPressedColor() { return default_text_pressed_color; }

        static void defaultBorderColor(SDL_Color c) { default_border_color = c; }
        static void defaultBorderColor(int r, int g, int b, int a=255) { default_border_color = (SDL_Color){r, g, b, a}; }
        static SDL_Color defaultBorderColor() { return default_border_color; }

        static void defaultFont(Font *f) { default_font = f; }
        static void defaultFont(string f_str) { default_font = dynamic_cast<Font*>(Asset::get(f_str)); }
        static Font* defaultFont() { return default_font;}

    protected:
        int type_id;
        PosObj pos;
        SDL_Rect dimen;

        vector<Panel*> child_list;
        Panel* parent_panel;

        Image *background_image;
        SDL_Rect back_clip;

        SDL_Color text_off_color;
        SDL_Color text_on_color;
        SDL_Color text_pressed_color;

        SDL_Color back_off_color;
        SDL_Color back_on_color;
        SDL_Color back_pressed_color;

        SDL_Color border_color;

        SDL_Surface* text_srf;
        Font *fnt;

        string text;
        string old_text;
        string tooltip_text;

        int b_width;

        bool hidden;
        bool show_background;
        bool show_border;

        bool mouse_inside;
        bool mouse_focus;

        bool clicked;

        Vector2D sel_off;
        bool selected;

        static SDL_Color default_bg_on_color;
        static SDL_Color default_bg_off_color;
        static SDL_Color default_bg_pressed_color;

        static SDL_Color default_fg_on_color;
        static SDL_Color default_fg_off_color;
        static SDL_Color default_fg_pressed_color;

        static SDL_Color default_text_on_color;
        static SDL_Color default_text_off_color;
        static SDL_Color default_text_pressed_color;

        static SDL_Color default_border_color;

        static Font* default_font;

        bool bg_on_set;
        bool bg_off_set;
        bool bg_pressed_set;

        bool fg_on_set;
        bool fg_off_set;
        bool fg_pressed_set;

        bool t_on_set;
        bool t_off_set;
        bool t_pressed_set;

        bool b_col_set;

        bool back_image;
        bool b_clip_set;

        virtual void updateText();
};

#endif // PANEL_H
