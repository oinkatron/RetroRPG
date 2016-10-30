#include "../include/Font.h"

string Font::font_path = "res/fonts/";
string Font::font_exten = ".ttf";

bool Font::onLoad(string f_name)
{
    if (Asset::get(f_name))
    {
        Log::game_log->pushError("Asset with name: " + f_name + " already exists!");
        return false;
    }
    string *spl_str = split(f_name, ":");
    Font *new_font;

    new_font = new Font();
    if (!new_font)
        return false;

    new_font->Name(f_name);
    new_font->Size(atoi(spl_str[1].c_str()));
    new_font->fnt = TTF_OpenFont((font_path + spl_str[0] + font_exten).c_str(), new_font->Size());
    if (!new_font->fnt)
    {
        Log::game_log->pushError("Error Opening font: " + font_path + spl_str[0] + font_exten);
        delete new_font;
        return false;
    }

    Asset::add(new_font);
    return true;
}


Font::~Font()
{
    TTF_CloseFont(fnt);
    size = 0;
}
