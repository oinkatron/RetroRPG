#include "../include/EditState.h"

EditState EditState::edit_state;

EditState::EditState()
{
    //ctor
}

EditState::~EditState()
{
    //dtor
}

void EditState::onLoad()
{
    Image::onLoad("icons.bmp");
    Image::onLoad("chars.png");
    Font::onLoad("main:14");
    Font::onLoad("main:10");
    SpriteBase::onLoad("test");

    top_bar = new Panel();
    top_bar->setDimensions(800, 24);
    top_bar->setPosition(0, 0);
    top_bar->Hidden(false);
    top_bar->showBackground(true);
    top_bar->backColor(76, 76, 76);

    win_map_info = new Panel();
    win_map_info->setDimensions(175, 400);
    win_map_info->setPosition(400, 50);
    win_map_info->backColor(32, 32, 176);
    win_map_info->borderColor(255, 255, 255);
    win_map_info->borderWidth(4);
    win_map_info->Hidden(false);
    win_map_info->showBackground(true);
    win_map_info->showBorder(true);

    tp_sv_btn = new Button();
    tp_sv_btn->setDimensions(32, 32);
    tp_sv_btn->setPosition(25, 0);
    tp_sv_btn->tooltipText("Save Map");
    tp_sv_btn->backgroundImage("icons.bmp");
    tp_sv_btn->backImageClip(110, 2, 24, 24);
    tp_sv_btn->Hidden(false);
    tp_sv_btn->showBackground(true);
    top_bar->addChild(tp_sv_btn);

    tp_ld_btn = new Button();
    tp_ld_btn->tooltipText("Load Map");
    tp_ld_btn->setDimensions(24, 24);
    tp_ld_btn->setPosition(0, 0);
    tp_ld_btn->backgroundImage("icons.bmp");
    tp_ld_btn->backImageClip(12, 2, 24, 24);
    tp_ld_btn->Hidden(false);
    tp_ld_btn->showBackground(true);
    top_bar->addChild(tp_ld_btn);

    map_width_box = new TextBox();
    map_width_box->textFont(dynamic_cast<Font*>(Asset::get("main:10")));
    map_width_box->Text("01");
    map_width_box->setDimensions(35, 14);
    map_width_box->setPosition(120, 7);
    map_width_box->showBackground(true);
    map_width_box->borderColor(0, 0, 0);
    map_width_box->Hidden(false);
    map_width_box->showBorder(true);
    win_map_info->addChild(map_width_box);

    map_height_box = new TextBox();
    map_height_box->textFont(dynamic_cast<Font*>(Asset::get("main:10")));
    map_height_box->Text("01");
    map_height_box->setDimensions(35, 14);
    map_height_box->setPosition(120, 27);
    map_height_box->showBackground(true);
    map_height_box->borderColor(0, 0, 0);
    map_height_box->Hidden(false);
    map_height_box->showBorder(true);
    win_map_info->addChild(map_height_box);

    map_width_label = new Label("Map Width:", "main:10", SDL_Color{0, 0, 0, 0});
    map_width_label->setPosition(10, 10);
    map_width_label->Hidden(false);
    win_map_info->addChild(map_width_label);

    map_height_label = new Label("Map Height:", "main:10", SDL_Color{0, 0, 0, 0});
    map_height_label->setPosition(10, 30);
    map_height_label->Hidden(false);
    win_map_info->addChild(map_height_label);

    setup_win = new Panel();
    setup_win->setDimensions(400, 256);
    setup_win->setPosition(200, 162);
    setup_win->backColor(128, 128, 128);
    setup_win->borderColor(255, 255, 255);
    setup_win->borderWidth(5);
    setup_win->Hidden(false);
    setup_win->showBackground(true);
    setup_win->showBorder(true);

    n_map_btn = new Button("walk_left", "", "NEW_MAP");

    //n_map_btn->textFont((Font*)Asset::get("main:14"));
    //n_map_btn->textColor(255, 255, 255);
    n_map_btn->Hidden(false);
    n_map_btn->setPosition(20, 20);
    setup_win->addChild(n_map_btn);

    l_map_btn = new Button("Load Map", "LOAD_MAP");
    l_map_btn->textFont((Font*)Asset::get("main:14"));
    l_map_btn->showBackground(true);
    l_map_btn->showBorder(true);
    l_map_btn->Hidden(false);
    l_map_btn->setPosition(20, 120);
    l_map_btn->setDimensions(100, 60);
    setup_win->addChild(l_map_btn);

    Panel::addWindow(setup_win);
    Panel::addWindow(top_bar);
    Panel::addWindow(win_map_info);

    Log::game_log->pushLog("Finished setting up edit mode");

}

void EditState::onUnload()
{

}

void EditState::onEvent(GameEvent *ge)
{

}

void EditState::onLoop()
{

}

void EditState::onDraw(Graphics &g)
{
    g.setColor(0,0,0);
    g.drawRect(0, 0, 800, 600);
}
