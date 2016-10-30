#include "../include/MenuState.h"

MenuState MenuState::menu_state;

MenuState::MenuState()
{
    clip = (SDL_Rect){0, 0, 0, 0};
}

void MenuState::onEvent(GameEvent *ge)
{
    GEvent *e;
    while((e = ge->pollEvent()) != NULL)
    {
        switch (e->type)
        {
            case GE_BUTTONRELEASED:
            {
                if (e->action == "N_GAME")
                {
                    Log::game_log->pushLog("Textbox contents: " + box->Text());
                    if (c_box->isChecked())
                       Log::game_log->pushLog("Random check box checked");
                    if (lol_box->isChecked())
                        Log::game_log->pushLog("LOLOLOLOLOLOLOL");
                    if (idk_box->isChecked())
                        Log::game_log->pushLog("Imagine something awesome happened!");
                    GameState::popState();
                    SDL_Delay(1000);
                    GameState::pushState(&PlayState::play_state);
                }
                else if (e->action == "E_GAME")
                {
                    GameState::popState();
                    SDL_Delay(1000);
                    GameState::pushState(&EditState::edit_state);
                }
                break;
            }
            case GE_TEXTBOX_TEXTCHANGED:
            {
                if (e->action == "TITLE_CHANGED")
                {
                    Log::game_log->pushLog("Updated Title Text :)");
                }
                break;
            }
        }

    }
}

void MenuState::onLoad()
{
    Font::onLoad("main:24");
    Font::onLoad("main:10");
    Font::onLoad("main:14");

    win = new Panel();
    win->setDimensions(400, 268);
    win->setPosition(200, 200);
    win->backColor(128, 128, 128);
    win->borderColor(0, 0, 64);
    win->borderWidth(2);
    win->Hidden(false);
    win->showBorder(true);
    win->showBackground(true);
    Panel::addWindow(win);

    n_game = new Button();
    n_game->Text("New Game");
    n_game->tooltipText("Start the game");
    n_game->textFont((Font*)Asset::get("main:24"));
    n_game->textColor(255, 0, 0);
    n_game->textOnColor(255, 0, 128);
    n_game->textOffColor(255,0 ,0);
    n_game->setAction("N_GAME");
    n_game->backColor(128, 0, 0);
    n_game->backOffColor(128, 0, 128);
    n_game->Hidden(false);
    n_game->showBackground(true);
    n_game->showBorder(true);
    n_game->setDimensions(335, 50);
    n_game->setPosition(19, 42);
    win->addChild(n_game);

    e_game = new Button();
    e_game->Text("Edit Game");
    e_game->tooltipText("Edit the game");
    e_game->textFont((Font*)Asset::get("main:24"));
    e_game->textColor(255, 0, 0);
    e_game->textOnColor(255,0, 128);
    e_game->textOffColor(255, 0, 0);
    e_game->setAction("E_GAME");
    e_game->backColor(128, 0, 0);
    e_game->backOffColor(128, 0, 128);
    e_game->Hidden(false);
    e_game->showBackground(true);
    e_game->showBorder(true);
    e_game->setDimensions(335, 50);
    e_game->setPosition(19, 180);
    win->addChild(e_game);

    dd_box = new DropDownBox();
    dd_box->setDimensions(100, 16);
    dd_box->setPosition(200, 120);
    dd_box->textFont((Font*)Asset::get("main:14"));
    dd_box->textColor(0, 0, 0);
    dd_box->backColor(255, 255, 255);
    dd_box->borderColor(0, 0, 0);
    dd_box->Hidden(false);
    dd_box->showBackground(true);
    dd_box->showBorder(true);
    win->addChild(dd_box);

    box = new TextBox();
    box->textFont(dynamic_cast<Font*>(Asset::get("main:14")));
    box->Text("Default Text");
    box->setDimensions(200, 16);
    box->setPosition(10, 100);
    box->showBackground(true);
    box->Hidden(false);
    box->showBorder(true);
    box->Action("TITLE_CHANGED");
    win->addChild(box);

    c_box = new CheckBox();
    c_box->setPosition(10, 120);
    c_box->Hidden(false);
    win->addChild(c_box);

    lol_box = new CheckBox();
    lol_box->setPosition(10, 140);
    lol_box->Hidden(false);
    win->addChild(lol_box);

    idk_box = new CheckBox();
    idk_box->setPosition(10, 160);
    idk_box->Hidden(false);
    win->addChild(idk_box);

    c_box_lbl = new Label("Random Checkbox", "main:10", (SDL_Color){0, 0, 0, 0});
    c_box_lbl->setPosition(30, 120);
    c_box_lbl->Hidden(false);
    win->addChild(c_box_lbl);

    lol_box_lbl = new Label("This Checkbox lolz ^_^", "main:10", (SDL_Color){0, 0, 0, 0});
    lol_box_lbl->setPosition(30, 140);
    lol_box_lbl->Hidden(false);
    win->addChild(lol_box_lbl);

    idk_box_lbl = new Label("Idk what this box does lul", "main:10", (SDL_Color){0, 0, 0, 0});
    idk_box_lbl->setPosition(30, 160);
    idk_box_lbl->Hidden(false);
    win->addChild(idk_box_lbl);
}

void MenuState::onUnload()
{
    Asset::remove("main:42");
    Asset::remove("main:10");
    Asset::remove("ctlogo.png");

    Panel::flush();
}

void MenuState::onLoop()
{
    for (int i = 0; i < Streamer::streamer_list.size(); i++)
    {
        Streamer::streamer_list[i]->onLoop();
    }
}

void MenuState::onDraw(Graphics &g)
{
    g.setColor(0, 32, 64);
    g.drawRect(0, 0, Camera::cam.W(), Camera::cam.H());

    for (int i = 0; i < Streamer::streamer_list.size(); i++)
    {
        for (int ii = 0; ii < Streamer::streamer_list[i]->parts.size(); ii++)
        {
            if (Streamer::streamer_list[i]->parts[ii] && Streamer::streamer_list[i]->parts[ii]->active)
            {
                clip = Streamer::streamer_list[i]->parts[ii]->clip_rect;

                if (Camera::cam.isInside(clip))
                {
                    if (Streamer::streamer_list[i]->parts[ii]->sprite)
                    {
                        g.drawSprite(clip.x-Camera::cam.X(), clip.y-Camera::cam.Y(), Streamer::streamer_list[i]->parts[ii]->sprite);
                    }
                    else
                    {
                        g.setColor(Streamer::streamer_list[i]->parts[ii]->color.r, Streamer::streamer_list[i]->parts[ii]->color.g, Streamer::streamer_list[i]->parts[ii]->color.b);
                        g.drawRect(clip.x-Camera::cam.X(), clip.y-Camera::cam.Y(), clip.w, clip.h);
                    }
                }
            }
        }
    }
}

MenuState::~MenuState()
{
    //dtor
}
