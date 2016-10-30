#include "../include/PlayState.h"

PlayState PlayState::play_state;

PlayState::PlayState()
{
    m_map = NULL;
    selected_obj = NULL;

    debug_mode = false;
    chat_active = false;
    clip = (SDL_Rect){0, 0, 0, 0};

}

void PlayState::onLoop()
{
    for (int i = 0; i < Streamer::streamer_list.size(); i++)
    {
        Streamer::streamer_list[i]->onLoop();
    }

    map<string, Object*>::iterator itr = Object::obj_bank.begin();
    for (itr = Object::obj_bank.begin(); itr != Object::obj_bank.end(); itr++)
    {
        if (itr->second != selected_obj)
            itr->second->onLoop();
    }

    for (int i = 0; i < ObjectCollision::col_list.size(); i++)
    {
        ObjectCollision::col_list[i]->a->onCollision(ObjectCollision::col_list[i]->b, ObjectCollision::col_list[i]->t);
        delete ObjectCollision::col_list[i];
    }

    ObjectCollision::col_list.clear();

    //Update Camera
    Camera::cam.onLoop();
}


void PlayState::onEvent(GameEvent *ge)
{
    GEvent *e;
    while((e = ge->pollEvent()) != NULL)
    {
        switch(e->type)
        {
            case GE_KEYDOWN:
            {
                switch (e->keycode)
                {
                    case SDLK_o:
                    {
                        m_map->saveMap("test");
                        break;
                    }
                    case SDLK_i:
                    {
                        m_map->loadMap("test");
                        break;
                    }
                    case SDLK_g:
                    {
                        m_map->drawGrid(!m_map->drawGrid());
                        break;
                    }

                }

                for (obj_itr = Object::obj_bank.begin(); obj_itr != Object::obj_bank.end(); obj_itr++)
                {
                    if (obj_itr->second != selected_obj)
                        obj_itr->second->handleKeyInput(e->keycode, true);
                }

                break;
            }
            case GE_KEYUP:
            {
                for (obj_itr = Object::obj_bank.begin(); obj_itr != Object::obj_bank.end(); obj_itr++)
                {
                    if (obj_itr->second != selected_obj)
                        obj_itr->second->handleKeyInput(e->keycode, false);
                }
                break;
            }
            case GE_MOUSEMOVE:
            {
                mouse_p.X(e->mouse_p->X() + Camera::cam.X());
                mouse_p.Y(e->mouse_p->Y() + Camera::cam.Y());
                break;
            }
            case GE_MOUSEPRESSED:
            {
                mouse_p.X(e->mouse_p->X() + Camera::cam.X());
                mouse_p.Y(e->mouse_p->Y() + Camera::cam.Y());

                if (e->mouse_b == SDL_BUTTON_LEFT)
                {
                    if (m_map)
                    {
                        if (mouse_p.X() >= 0 && mouse_p.X() <= m_map->Width() && mouse_p.Y() >= 0 && mouse_p.Y() <= m_map->Height())
                        {
                            Tile* t = m_map->getTile(mouse_p.X()/m_map->tileSize(), mouse_p.Y()/m_map->tileSize());
                            if (t)
                            {
                                t->id = 6;
                                t->type = TILE_BLANK;
                            }
                        }
                    }

                }
                else if (e->mouse_b== SDL_BUTTON_RIGHT)
                {
                    if (m_map)
                    {
                        if (mouse_p.X() >= 0 && mouse_p.X() <= m_map->Width() && mouse_p.Y() >= 0 && mouse_p.Y() <= m_map->Height())
                        {
                            Tile *t = m_map->getTile(mouse_p.X()/m_map->tileSize(), mouse_p.Y()/m_map->tileSize());
                            if (t)
                            {
                                t->id = 0;
                                t->type = TILE_NULL;
                            }
                        }
                    }
                }
                break;
            }
            case GE_MOUSERELEASED:
            {
                mouse_p.X(e->mouse_p->X() + Camera::cam.X());
                mouse_p.Y(e->mouse_p->Y() + Camera::cam.Y());

                for (obj_itr = Object::obj_bank.begin(); obj_itr != Object::obj_bank.end(); obj_itr++)
                {
                        obj_itr->second->getPosition()->Anchor(NULL);
                }
                break;
            }

            case GE_BUTTONPRESSED:
            {
                if (e->action == "Moo")
                {
                    Log::game_log->pushLog("Ready to moo!");
                }

                break;
            }
            case GE_BUTTONRELEASED:
            {
                if (e->action == "Moo")
                {
                    Log::game_log->pushLog("I moo'd Moo!");
                }

                break;
            }
            case GE_CHATEVENT:
            {
                text_box->initMessage(e->chat_info->name, e->chat_info->msg, e->chat_info->portrait);
                text_box->renderLines();
                text_box->Hidden(false);
                Panel::focused_panel = text_box;
            }
        }
    }
}

void PlayState::onDraw(Graphics &g)
{
    int sx, ex, sy, ey;

    DrawEvent *new_d = NULL;
    //clear the screen
    if (m_map)
    {
        g.setLayer(Graphics::LAYER_BACKGROUND);
        new_d = new DrawEvent;
        new_d->type = DRAW_RECT;
        new_d->r = {0, 0, Camera::cam.W(), Camera::cam.H()};
        new_d->color = m_map->backgroundColor();
        g.addDrawEvent(new_d);

        if (m_map->backgroundImage())
        {
            g.setLayer(Graphics::LAYER_BACKGROUND);
            new_d = new DrawEvent;
            new_d->type = DRAW_IMAGE;
            new_d->asset = (void*)m_map->backgroundImage();
            new_d->clip = m_map->backgroundClip(Camera::cam.gameClip(), Camera::cam.follow()->getPosition());
            new_d->img_clipped = true;
            new_d->depth = 10;
            new_d->r.x = m_map->backgroundOffset()->X();
            new_d->r.y = m_map->backgroundOffset()->Y();

            g.addDrawEvent(new_d);
        }
    }
    else
    {
        g.setLayer(Graphics::LAYER_BACKGROUND);
        new_d = new DrawEvent;
        new_d->type = DRAW_RECT;
        new_d->depth = 10;
        new_d->color = {64, 64, 64, 255};
        new_d->r = {0, 0, Camera::cam.W(), Camera::cam.H()};

        g.addDrawEvent(new_d);
    }

    if (Camera::cam.X() <= 0)
    {
        sx = 0;
    }
    else
    {
        sx = Camera::cam.X()/m_map->tileSize();
    }

    if (Camera::cam.Y() <= 0)
    {
        sy = 0;
    }
    else
    {
        sy = Camera::cam.Y()/m_map->tileSize();
    }

    if ((Camera::cam.W()+Camera::cam.X())/m_map->tileSize() +1 >= m_map->mapWidth())
    {
        ex = m_map->mapWidth();
    }
    else
    {
        ex = (Camera::cam.W()+Camera::cam.X())/m_map->tileSize()+1;
    }

    if (((Camera::cam.H()+Camera::cam.Y())/m_map->tileSize())+1 >= m_map->mapHeight())
    {
        ey = m_map->mapHeight();
    }
    else
    {
        ey = (Camera::cam.H()+Camera::cam.Y())/m_map->tileSize()+1;
    }

    g.setLayer(Graphics::LAYER_TILE);
    if (m_map)
    {
        for (int i = sx; i < ex; i ++)
        {
            for (int ii = sy; ii < ey; ii ++)
            {
                if ((m_map->getTile(i, ii)) && m_map->getTile(i, ii)->type != TILE_NULL)
                {
                    if (m_map->tileSheet())
                    {
                        new_d = new DrawEvent;
                        new_d->type = DRAW_IMAGE;
                        new_d->depth = 1;
                        new_d->clip = m_map->tileSheet()->getClip(m_map->getTile(i, ii)->id);
                        new_d->img_clipped = true;
                        new_d->asset = (void*)m_map->tileSheet()->Raw();
                        new_d->r.x = i*m_map->tileSize()-Camera::cam.X();
                        new_d->r.y = ii*m_map->tileSize()-Camera::cam.Y();
                        g.addDrawEvent(new_d);
                    }
                }
            }
        }

        /*if (m_map->drawGrid())
        {
            g.setColor(255, 255, 255);
            for (int i = sx; i < ex; i++)
            {
                g.drawRect(i*m_map->tileSize()-Camera::cam.X(), (sy*m_map->tileSize())-Camera::cam.Y(), 1, (ey-sy)*m_map->tileSize());
            }

            for (int i = sy; i < ey; i++)
            {
                g.drawRect((sx*m_map->tileSize())-Camera::cam.X(), i*m_map->tileSize()-Camera::cam.Y(), (ex-sx)*m_map->tileSize(), 1);
            }
        }*/
    }

    /*for (int i = 0; i < Streamer::streamer_list.size(); i++)
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
    }*/

    g.setLayer(Graphics::LAYER_OBJECT);
    map<string, Object*>::iterator itr = Object::obj_bank.begin();
    for (itr; itr != Object::obj_bank.end(); itr++)
    {
        if (Camera::cam.isInside(itr->second->getBounds()))
        {
            if (itr->second)
            {
                new_d = new DrawEvent;
                new_d->type = DRAW_OBJECT;
                new_d->depth = (itr->second->Depth() >= 0) ? (int)itr->second->Y() : itr->second->Depth();
                new_d->asset = (void*)itr->second;
                new_d->r.x = itr->second->X() - itr->second->xOrigin() - Camera::cam.X();
                new_d->r.y = itr->second->Y() - itr->second->yOrigin() - Camera::cam.Y();
                g.addDrawEvent(new_d);
                //g.drawObject(itr->second->X() - itr->second->xOrigin() - Camera::cam.X(), itr->second->Y() - itr->second->yOrigin() - Camera::cam.Y(), itr->second);
                /*if (debug_mode)
                {
                    g.setColor(0, 0, 255);
                    g.drawBox(itr->second->boxX()-Camera::cam.X(), itr->second->boxY()- Camera::cam.Y(), itr->second->W(), itr->second->H(), 3);

                    g.setColor(255,0,0);
                    g.drawRect((int)itr->second->X() - 2 - Camera::cam.X(), (int)itr->second->Y() - 2 - Camera::cam.Y(), 4, 4);

                    if (m_map)
                    {
                        g.setColor(255,255,0);
                        g.drawBox(itr->second->mapX()*m_map->tileSize() - Camera::cam.X(), itr->second->mapY()*m_map->tileSize() - Camera::cam.Y(), m_map->tileSize(), m_map->tileSize(), 3);

                        g.setColor(255,0,0);
                        switch (dynamic_cast<ObjNPC*>(itr->second)->curDirection())
                        {
                            case DIR_UP:
                                g.drawBox(itr->second->mapX()*m_map->tileSize() - Camera::cam.X(), (itr->second->mapY()-1)*m_map->tileSize() - Camera::cam.Y(), m_map->tileSize(), m_map->tileSize(), 3);
                            break;
                            case DIR_DOWN:
                                g.drawBox(itr->second->mapX()*m_map->tileSize() - Camera::cam.X(), (itr->second->mapY()+1)*m_map->tileSize() - Camera::cam.Y(), m_map->tileSize(), m_map->tileSize(), 3);
                            break;
                            case DIR_LEFT:
                                g.drawBox((itr->second->mapX()-1)*m_map->tileSize() - Camera::cam.X(), itr->second->mapY()*m_map->tileSize() - Camera::cam.Y(), m_map->tileSize(), m_map->tileSize(), 3);
                            break;
                            case DIR_RIGHT:
                                g.drawBox((itr->second->mapX()+1)*m_map->tileSize() - Camera::cam.X(), itr->second->mapY()*m_map->tileSize() - Camera::cam.Y(), m_map->tileSize(), m_map->tileSize(), 3);
                            break;
                        }
                    }
                }*/
            }
        }
    }

    /*if (m_map)
    {
        if (m_map->foregroundImage())
        {
            SDL_Rect tmp = m_map->foregroundClip(Camera::cam.gameClip(), Camera::cam.follow()->getPosition());
            g.drawImage(m_map->foregroundOffset()->X(), m_map->foregroundOffset()->Y(), m_map->foregroundImage(), &tmp);
        }
    }*/

    //Draw FPS in top corner
    g.setLayer(Graphics::LAYER_FOREGROUND);
    new_d = new DrawEvent;
    new_d->type = DRAW_STRING;
    new_d->depth = 100;
    new_d->msg = "FPS: " + toString(Timer::fps.getFPS());
    new_d->color = {255, 255, 255, 255};
    new_d->r = {0, 0, 0, 0};

    g.addDrawEvent(new_d);
}

void PlayState::onLoad()
{
    Image::onLoad("tag.png");
    Image::onLoad("chars.png");
    Image::onLoad("portrait.png");
    Font::onLoad("main:24");
    Font::onLoad("main:20");
    SpriteBase::onLoad("test");
    Tilesheet::onLoad("test");

    toggleDebug();

    text_box = new TextWindow();
    text_box->textOffColor(255, 255, 255);
    text_box->textFont((Font*)Asset::get("main:14"));
    text_box->setPosition(95, 400);
    text_box->setDimensions(500, 75);
    text_box->showBackground(true);
    text_box->backColor(0, 0, 128);
    text_box->showBorder(true);
    text_box->borderColor(255, 255, 255);
    text_box->borderWidth(5);
    text_box->Hidden(true);
    text_box->horizontalPadding(56);
    text_box->verticalPadding(2);
    text_box->maxLines(-1);
    text_box->actionKey(SDLK_z);
    Panel::addWindow(text_box);

    m_map = new Map();
    m_map->loadMap("test");

    ControlScheme cont;
    cont.upKey(SDLK_UP);
    cont.downKey(SDLK_DOWN);
    cont.rightKey(SDLK_RIGHT);
    cont.leftKey(SDLK_LEFT);
    cont.actionA(SDLK_z);
    cont.actionB(SDLK_x);

    Player* obj = new Player("Coatale");
    p = obj;
    obj->startX(100);
    obj->startY(100);
    obj->W(16);
    obj->H(16);
    obj->xOrigin(16);
    obj->yOrigin(24);
    obj->X(100);
    obj->Y(100);
    obj->Local(m_map);
    obj->maxVel(125);
    obj->canMove(true);
    obj->Gravity(false);
    obj->Solid(true);
    obj->Controls(cont);
    obj->WalkLeftSprite("walk_left");
    obj->WalkRightSprite("walk_right");
    obj->WalkUpSprite("walk_up");
    obj->WalkDownSprite("walk_down");
    obj->LeftSprite("stand_left");
    obj->RightSprite("stand_right");
    obj->UpSprite("stand_up");
    obj->DownSprite("stand_down");
    obj->sprite(obj->WalkLeftSprite());

    ObjNPC *npc = new ObjNPC("npc_01");
    npc->W(16);
    npc->H(16);
    npc->xOrigin(16);
    npc->yOrigin(24);
    npc->X(200);
    npc->Y(100);
    npc->Solid(true);
    npc->Local(m_map);
    npc->sprite("stand_down");
    npc->charName("Tom");
    npc->chatPortrait((Image*)Image::get("portrait.png"));
    if (npc->chatPortrait())
    {
        Log::game_log->pushLog("Portrait Image Loaded");
    }
    npc->chatText("I am some really interesting text that im sure ur just loving and reading right now ;) baby");

    Camera::cam.follow(obj);

    Log::game_log->pushLog("Number of assets: " + toString(Asset::asset_bank.size()));
}

void PlayState::onUnload()
{

}

PlayState::~PlayState()
{
    //dtor
}
