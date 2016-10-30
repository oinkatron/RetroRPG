#include "../include/GameInstance.h"

int GameInstance::screen_height;
int GameInstance::screen_width;
int GameInstance::screen_bpp;
int GameInstance::game_fps;
int GameInstance::game_speed;

GameInstance::GameInstance()
{
    game_fps = 0;
    screen_width = 0;
    screen_height = 0;
    screen_bpp = 0;

    screen = NULL;
    done = false;

    mouse_pos.X(0);
    mouse_pos.Y(0);
}

GameInstance::~GameInstance()
{
    Streamer::streamer_list.clear();
    SDL_Quit();
}

void GameInstance::transToPlay()
{
    GameState::pushState(&MenuState::menu_state);
}

bool GameInstance::init()
{
    DataFile init_file;
    bool log_file, log_console, f_screen;

    if (!init_file.loadFile("settings.cfg"))
    {
        Log::game_log->logToConsole(true);
        Log::game_log->logToFile(true);
        Log::game_log->pushError("Unable to find default config! Using default settings!");

        screen_width = 800;
        screen_height = 600;
        screen_bpp = 32;
        game_fps = 60;
        game_speed = 1.0f;
        f_screen = false;
    }
    else
    {
        if (!init_file.getMember("Settings", "log_to_console", &log_console))
        {
            log_console = true;
            Log::game_log->logToConsole(true);
            Log::game_log->pushError("log_to_console not found! Assuming true!");
        }
        Log::game_log->logToConsole(log_console);

        if (!init_file.getMember("Settings", "log_to_file", &log_file))
        {
            log_file = true;
            Log::game_log->pushError("log_to_file not found! Assuming true!");
        }
        Log::game_log->logToFile(log_file);

        if (!init_file.getMember("Settings", "screen_width", &screen_width))
        {
            Log::game_log->pushError("screen_width not found! Assuming 800");
            screen_width = 800;
        }

        if (!init_file.getMember("Settings", "screen_height", &screen_height))
        {
            Log::game_log->pushError("screen_height not found! Assuming 600");
            screen_height = 600;
        }

        if (!init_file.getMember("Settings", "screen_bpp", &screen_bpp))
        {
            Log::game_log->pushError("screen_bpp not found! Assuming 32");
            screen_bpp = 32;
        }

        if (!init_file.getMember("Settings", "fullscreen", &f_screen))
        {
            Log::game_log->pushError("fullscreen not found! Assuming false!");
            f_screen = false;
        }

        if (!init_file.getMember("Settings", "fps", &game_fps))
        {
            Log::game_log->pushError("fps not found! Assuming 60");
            game_fps = 60;
        }

        if (!init_file.getMember("Settings", "speed", &game_speed))
        {
            Log::game_log->pushError("speed not found! Assuming 1.0");
            game_speed = 1.0f;
        }

        /*Load UI defaults*/
        int t_r = 0, t_g = 0, t_b = 0;

        if (!init_file.getMember("UI", "background_off_r", &t_r))
        {
            Log::game_log->pushError("Background red value not found! Assuming 0");
            t_r = 0;
        }

        if (!init_file.getMember("UI", "background_off_g", &t_g))
        {
            Log::game_log->pushError("Background green value not found! Assuming 0");
            t_g = 0;
        }

        if (!init_file.getMember("UI", "background_off_b", &t_b))
        {
            Log::game_log->pushError("Background  blue value not found! Assuming 0");
            t_b = 0;
        }

        Panel::defaultBackgroundOffColor(t_r, t_g, t_b);

        if (!init_file.getMember("UI", "background_on_r", &t_r))
        {
            Log::game_log->pushError("Background Hover red value not found! Assuming 0");
            t_r = 0;
        }

        if (!init_file.getMember("UI", "background_on_g", &t_g))
        {
            Log::game_log->pushError("Background Hover green value not found! Assuming 0");
            t_g = 0;
        }

        if (!init_file.getMember("UI", "background_on_b", &t_b))
        {
            Log::game_log->pushError("Background Hover blue value not found! Assuming 0");
            t_b = 0;
        }

        Panel::defaultBackgroundOnColor(t_r, t_g, t_b);

        if (!init_file.getMember("UI", "background_pressed_r", &t_r))
        {
            Log::game_log->pushError("Background Pressed red value not found! Assuming 0");
            t_r = 0;
        }

        if (!init_file.getMember("UI", "background_pressed_g", &t_g))
        {
            Log::game_log->pushError("Background Hover green value not found! Assuming 0");
            t_g = 0;
        }

        if (!init_file.getMember("UI", "background_pressed_b", &t_b))
        {
            Log::game_log->pushError("Background Pressed blue value not found! Assuming 0");
            t_b = 0;
        }

        Panel::defaultBackgroundPressedColor(t_r, t_g, t_b);

        if (!init_file.getMember("UI", "text_off_r", &t_r))
        {
            Log::game_log->pushError("Text red value not found! Assuming 0");
            t_r = 0;
        }

        if (!init_file.getMember("UI", "text_off_g", &t_g))
        {
            Log::game_log->pushError("Text green value not found! Assuming 0");
            t_g = 0;
        }

        if (!init_file.getMember("UI", "text_off_b", &t_b))
        {
            Log::game_log->pushError("Text blue value not found! Assuming 0");
            t_b = 0;
        }

        Panel::defaultTextOffColor(t_r, t_g, t_b);

        if (!init_file.getMember("UI", "text_on_r", &t_r))
        {
            Log::game_log->pushError("Text Hover red value not found! Assuming 0");
            t_r = 0;
        }

        if (!init_file.getMember("UI", "text_on_g", &t_g))
        {
            Log::game_log->pushError("Text Hover green value not found! Assuming 0");
            t_g = 0;
        }

        if (!init_file.getMember("UI", "text_on_b", &t_b))
        {
            Log::game_log->pushError("Text Hover blue value not found! Assuming 0");
            t_b = 0;
        }

        Panel::defaultTextOnColor(t_r, t_g, t_b);

        if (!init_file.getMember("UI", "text_pressed_r", &t_r))
        {
            Log::game_log->pushError("Text Pressed red value not found! Assuming 0");
            t_r = 0;
        }

        if (!init_file.getMember("UI", "text_pressed_g", &t_g))
        {
            Log::game_log->pushError("Text Pressed green value not found! Assuming 0");
            t_g = 0;
        }

        if (!init_file.getMember("UI", "text_pressed_b", &t_b))
        {
            Log::game_log->pushError("Text Pressed blue value not found! Assuming 0");
            t_b = 0;
        }

        Panel::defaultTextPressedColor(t_r, t_g, t_b);

        if (!init_file.getMember("UI", "foreground_off_r", &t_r))
        {
            Log::game_log->pushError("Foreground red value not found! Assuming 0");
            t_r = 0;
        }

        if (!init_file.getMember("UI", "foreground_off_g", &t_g))
        {
            Log::game_log->pushError("Foreground green value not found! Assuming 0");
            t_g = 0;
        }

        if (!init_file.getMember("UI", "foreground_off_b", &t_b))
        {
            Log::game_log->pushError("Foreground blue value not found! Assuming 0");
            t_b = 0;
        }

        Panel::defaultForegroundOffColor(t_r, t_g, t_b);

        if (!init_file.getMember("UI", "foreground_on_r", &t_r))
        {
            Log::game_log->pushError("Foreground Hover red value not found! Assuming 0");
            t_r = 0;
        }

        if (!init_file.getMember("UI", "foreground_on_g", &t_g))
        {
            Log::game_log->pushError("Foreground Hover green value not found! Assuming 0");
            t_g = 0;
        }

        if (!init_file.getMember("UI", "foreground_on_b", &t_b))
        {
            Log::game_log->pushError("Foreground Hover blue value not found! Assuming 0");
            t_b = 0;
        }

        Panel::defaultForegroundOnColor(t_r, t_g, t_b);

        if (!init_file.getMember("UI", "foreground_pressed_r", &t_r))
        {
            Log::game_log->pushError("Foreground Pressed red value not found! Assuming 0");
            t_r = 0;
        }

        if (!init_file.getMember("UI", "foreground_pressed_g", &t_g))
        {
            Log::game_log->pushError("Foreground Pressed green value not found! Assuming 0");
            t_g = 0;
        }

        if (!init_file.getMember("UI", "foreground_pressed_b", &t_b))
        {
            Log::game_log->pushError("Foreground Pressed blue value not found! Assuming 0");
            t_b = 0;
        }

        Panel::defaultForegroundPressedColor(t_r, t_g, t_b);

        if (!init_file.getMember("UI", "border_r", &t_r))
        {
            Log::game_log->pushError("Border Red value not found! Assuming 0");
            t_r = 0;
        }

        if (!init_file.getMember("UI", "border_g", &t_g))
        {
            Log::game_log->pushError("Border Green value not found! Assuming 0");
            t_g = 0;
        }

        if (!init_file.getMember("UI", "border_b", &t_b))
        {
            Log::game_log->pushError("Border Blue value not found! Assuming 0");
            t_b = 0;
        }

        Panel::defaultBorderColor(t_r, t_g, t_b);

    }

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        Log::game_log->pushError("Failed to load SDL...closing");
        return false;
    }

    if (f_screen)
        screen = SDL_SetVideoMode(screen_width, screen_height, screen_bpp, SDL_FULLSCREEN | SDL_DOUBLEBUF);
    else
        screen = SDL_SetVideoMode(screen_width, screen_height, screen_bpp, SDL_HWSURFACE | SDL_DOUBLEBUF);

    if (!screen)
    {
        Log::game_log->pushError("Unable to set resolution!....exiting");
        return false;
    }

    if (TTF_Init() < 0)
    {
        Log::game_log->pushError("Could not start Font engine!...exiting");
        return false;
    }

    SDL_EnableUNICODE(SDL_ENABLE);

    Timer::fps.setFPS(game_fps);
    Timer::fps.setGameSpeed(game_speed);

    Font::onLoad("mailrays:20");
    Font::onLoad("mailrays:12");

    string def_fnt;
    if (!init_file.getMember("UI", "default_font", &def_fnt))
    {
        Log::game_log->pushError("Default Font not found! Using: mailrays:14");
        def_fnt = "mailrays:14";
    }

    Font::onLoad(def_fnt);
    Panel::defaultFont(def_fnt);

    g.setContext(screen);
    g.setColor(100, 100, 100);
    g.setFont((Font*)Asset::get("mailrays:20"));

    Camera::cam.init(screen_width, screen_height);

    Tooltip *tip_box;
    tip_box = new Tooltip();
    tip_box->showBorder(true);
    tip_box->showBackground(true);
    tip_box->setPosition(100, 100);
    tip_box->backColor(128, 128, 0);
    tip_box->borderColor(255, 255, 0);
    tip_box->borderWidth(1);
    tip_box->textColor(0, 0, 0);
    tip_box->maxWidth(400);
    tip_box->textFont(dynamic_cast<Font*>(Asset::get("mailrays:12")));
    Tooltip::tip_window = tip_box;
    PopupPanel::addPopup(tip_box);

    Log::game_log->pushLog("Finished Setup Starting game...:)");

    GameState::pushState(&StartUpState::start_state);
    new Alarm(transToPlay, 2000);
    return true;
}

void GameInstance::onLoop()
{
    while (!done)
    {
        Timer::fps.start();
        Timer::fps.onLoop();

        for (int i = 0; i < Alarm::alarm_bank.size(); i++)
        {
            Alarm::alarm_bank[i]->onLoop(i);
        }
        onEvent();

        for (int i = 0; i < Panel::panel_bank.size(); i++)
        {
            Panel::panel_bank[i]->onLoop();
        }

        if (GameState::state_stack.size() > 0)
        {
            GameState::state_stack[GameState::state_stack.size()-1]->onLoop();
        }

        onDraw();

        Timer::fps.limitFPS();
    }
}

void GameInstance::onDraw()
{
    if (GameState::state_stack.size() > 0)
    {
        GameState::state_stack[GameState::state_stack.size()-1]->onDraw(g);
    }

     g.processScene();

    for (int i = 0; i < Panel::panel_bank.size(); i++)
    {
        Panel::panel_bank[i]->onDraw(g);
    }

    for (int i = 0; i < PopupPanel::popup_list.size(); i++)
    {
        PopupPanel::popup_list[i]->onDraw(g);
    }

    SDL_Flip(screen);
}

void GameInstance::onEvent()
{
    if (GameState::state_change)
    {
        if (Tooltip::tip_window)
            Tooltip::tip_window->Hidden(true);

        Panel::hovered_panel = NULL;
        Panel::focused_panel = NULL;

        GameState::state_change = false;
    }

    GEvent* e;
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
            {
                done = true;
                Log::game_log->pushLog("Kill signal sent!");
                break;
            }
             case SDL_KEYDOWN:
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    if (Panel::focused_panel)
                    {
                        Panel::focused_panel->onKeyPress(event.key.keysym.sym, (SDL_GetModState() & KMOD_SHIFT));
                    }
                    else
                    {
                        done = true;
                    }
                }
                else
                {
                    if (Panel::focused_panel)
                    {
                        Panel::focused_panel->onKeyPress(event.key.keysym.sym, (SDL_GetModState() & KMOD_SHIFT));
                    }
                    else
                    {
                        e = new GEvent;
                        e->type = GE_KEYDOWN;
                        e->keycode = event.key.keysym.sym;
                        GameEvent::g_events.addEvent(e);
                    }
                }

                break;
            }
            case SDL_KEYUP:
            {
                if (!Panel::focused_panel)
                {
                    e = new GEvent;
                    e->type = GE_KEYUP;
                    e->keycode = event.key.keysym.sym;
                    GameEvent::g_events.addEvent(e);
                }

                break;
            }
            case SDL_MOUSEMOTION:
            {
                mouse_pos.X(event.motion.x);
                mouse_pos.Y(event.motion.y);

                bool brk_erly = false;

                for (int i = PopupPanel::popup_list.size()-1; i >= 0; i--)
                {
                    if (PopupPanel::popup_list[i]->isInside(mouse_pos.X(), mouse_pos.Y()))
                    {
                        Panel *tmp = PopupPanel::popup_list[i]->getClickedPanel(mouse_pos);
                        if (tmp)
                        {
                            mouse_pos.X(mouse_pos.X()-PopupPanel::popup_list[i]->X());
                            mouse_pos.Y(mouse_pos.Y()-PopupPanel::popup_list[i]->Y());
                            if(Panel::hovered_panel)
                            {
                                if (Panel::hovered_panel != tmp)
                                {
                                    Panel::hovered_panel->onExit();
                                    tmp->onEnter(mouse_pos);
                                    Panel::hovered_panel = tmp;
                                }
                                else
                                {
                                    tmp->onHover(mouse_pos);
                                }
                            }
                            else
                            {
                                tmp->onEnter(mouse_pos);
                                Panel::hovered_panel = tmp;
                            }
                            mouse_pos.X(mouse_pos.X() + PopupPanel::popup_list[i]->X());
                            mouse_pos.Y(mouse_pos.Y() + PopupPanel::popup_list[i]->Y());
                        }
                        else
                        {
                            if (Panel::hovered_panel)
                            {
                                if (Panel::hovered_panel != PopupPanel::popup_list[i])
                                {
                                    Panel::hovered_panel->onExit();
                                    PopupPanel::popup_list[i]->onEnter(mouse_pos);
                                    Panel::hovered_panel = PopupPanel::popup_list[i];
                                }
                                else
                                {
                                    PopupPanel::popup_list[i]->onHover(mouse_pos);
                                }
                            }
                            else
                            {
                                if (Panel::hovered_panel)
                                {
                                    Panel::hovered_panel = PopupPanel::popup_list[i];
                                    Panel::hovered_panel->onEnter(mouse_pos);
                                }
                            }
                        }

                        brk_erly = true;
                        break;
                    }
                    else
                    {
                        if (Panel::hovered_panel)
                        {
                            if (PopupPanel::popup_list[i] == Panel::hovered_panel)
                            {
                                Panel::hovered_panel->onExit();
                                Panel::hovered_panel = NULL;
                            }
                        }
                    }
                }

                if (!brk_erly)
                {
                    for (int i = Panel::panel_bank.size()-1; i >= 0; i--)
                    {
                        if (Panel::panel_bank[i]->isInside(mouse_pos.X(), mouse_pos.Y()))
                        {
                            Panel *tmp = Panel::panel_bank[i]->getClickedPanel(mouse_pos);
                            if (tmp)
                            {
                                mouse_pos.X(mouse_pos.X()-Panel::panel_bank[i]->X());
                                mouse_pos.Y(mouse_pos.Y()-Panel::panel_bank[i]->Y());

                                if(Panel::hovered_panel)
                                {
                                    if (Panel::hovered_panel != tmp)
                                    {
                                        Panel::hovered_panel->onExit();
                                        tmp->onEnter(mouse_pos);
                                        Panel::hovered_panel = tmp;
                                    }
                                    else
                                    {
                                        tmp->onHover(mouse_pos);
                                    }
                                }
                                else
                                {
                                    tmp->onEnter(mouse_pos);
                                    Panel::hovered_panel = tmp;
                                }

                                mouse_pos.X(mouse_pos.X()+Panel::panel_bank[i]->X());
                                mouse_pos.Y(mouse_pos.Y()+Panel::panel_bank[i]->Y());
                            }
                            else
                            {
                                if (Panel::hovered_panel)
                                {
                                    if (Panel::hovered_panel != Panel::panel_bank[i])
                                    {
                                        Panel::hovered_panel->onExit();
                                        Panel::panel_bank[i]->onEnter(mouse_pos);
                                        Panel::hovered_panel = Panel::panel_bank[i];
                                    }
                                    else
                                    {
                                        Panel::panel_bank[i]->onHover(mouse_pos);
                                    }
                                }
                                else
                                {
                                    if (Panel::hovered_panel)
                                    {
                                        Panel::hovered_panel = Panel::panel_bank[i];
                                        Panel::hovered_panel->onEnter(mouse_pos);
                                    }
                                }
                            }

                            brk_erly = true;
                            break;
                        }
                        else
                        {
                            if (Panel::hovered_panel)
                            {
                                if (Panel::panel_bank[i] == Panel::hovered_panel)
                                {
                                    Panel::hovered_panel->onExit();
                                    Panel::hovered_panel = NULL;
                                }
                            }
                        }
                    }
                }


                if (!Panel::focused_panel)
                {
                    e = new GEvent;
                    e->type = GE_MOUSEMOVE;
                    e->mouse_p = &mouse_pos;
                    GameEvent::g_events.addEvent(e);
                }

                if (Tooltip::tip_window && !Tooltip::tip_window->isHidden())
                {
                    Tooltip::tip_window->setPosition(mouse_pos.X()+10, mouse_pos.Y());
                }

                break;
            }
            case SDL_MOUSEBUTTONDOWN:
            {
                mouse_pos.X(event.button.x);
                mouse_pos.Y(event.button.y);

                Panel *tmp_fcsd = NULL;
                bool brk_erly = false;

                for (int i = PopupPanel::popup_list.size()-1; i >= 0; i--)
                {
                    if (PopupPanel::popup_list[i]->isInside(mouse_pos.X(), mouse_pos.Y()))
                    {
                        Panel::sel_panel = tmp_fcsd = PopupPanel::popup_list[i]->getClickedPanel(mouse_pos);
                        brk_erly = true;
                        break;
                    }
                }

                if (!brk_erly)
                {
                    for (int i = Panel::panel_bank.size()-1; i >= 0; i--)
                    {
                        if (Panel::panel_bank[i]->isInside(mouse_pos.X(), mouse_pos.Y()))
                        {
                            Panel::sel_panel = tmp_fcsd = Panel::panel_bank[i]->getClickedPanel(mouse_pos);
                            brk_erly = true;
                            break;
                        }
                    }
                }


                if (tmp_fcsd)
                {
                    if (Panel::focused_panel)
                    {
                        if (tmp_fcsd != Panel::focused_panel)
                        {
                            Panel::focused_panel->onUnfocus();
                            Panel::focused_panel = tmp_fcsd;
                            Panel::focused_panel->onFocus();
                        }

                        Panel::focused_panel->onClick(mouse_pos);
                    }
                    else
                    {
                        Panel::focused_panel = tmp_fcsd;
                        Panel::focused_panel->onFocus();
                    }
                }
                else
                {
                    if (Panel::focused_panel)
                    {
                        Panel::focused_panel->onUnfocus();
                        Panel::focused_panel = NULL;
                    }

                    e = new GEvent;
                    e->type = GE_MOUSEPRESSED;
                    e->mouse_p = &mouse_pos;
                    e->mouse_b = event.button.button;
                    GameEvent::g_events.addEvent(e);
                }


                break;
            }
            case SDL_MOUSEBUTTONUP:
            {
                mouse_pos.X(event.button.x);
                mouse_pos.Y(event.button.y);

                bool brk_erly = false;

                for (int i = PopupPanel::popup_list.size()-1; i >= 0; i--)
                {
                    if (PopupPanel::popup_list[i]->isInside(mouse_pos.X(), mouse_pos.Y()))
                    {
                        Panel *tmp = PopupPanel::popup_list[i]->getClickedPanel(mouse_pos);
                        if (tmp )
                        {
                            tmp->onRelease(mouse_pos);
                        }
                        brk_erly = true;
                        break;
                    }
                }

                if (!brk_erly)
                {
                    for (int i = Panel::panel_bank.size()-1; i >= 0; i--)
                    {
                        if (Panel::panel_bank[i]->isInside(mouse_pos.X(), mouse_pos.Y()))
                        {
                            Panel *tmp = Panel::panel_bank[i]->getClickedPanel(mouse_pos);
                            if (tmp )
                            {
                                tmp->onRelease(mouse_pos);
                            }
                            break;
                        }
                    }
                }

                if (Panel::sel_panel)
                {
                    //Panel::sel_panel->onRelease(mouse_pos);
                    Panel::sel_panel->isPressed(false);
                    Panel::sel_panel = NULL;
                }

                if (!Panel::focused_panel)
                {
                    e = new GEvent;
                    e->type = GE_MOUSERELEASED;
                    e->mouse_p = &mouse_pos;
                    e->mouse_b = event.button.button;
                    GameEvent::g_events.addEvent(e);
                }

                break;
            }
        }
    }

    if (GameState::state_stack.size() > 0)
    {
        GameState::state_stack[GameState::state_stack.size()-1]->onEvent(&GameEvent::g_events);
    }

    GameEvent::g_events.reset();
}
