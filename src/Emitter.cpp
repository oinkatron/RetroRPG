#include "../include/Emitter.h"

vector<Streamer*> Streamer::streamer_list;

string Emitter::part_path = "res/emitters/";
string Emitter::part_exten = ".emt";

Particle::Particle()
{
    x = 0;
    y = 0;
    life_span = 0;

    x_vel = 0;
    y_vel = 0;

    x_mod = 0;
    y_mod = 0;

    clip_rect = (SDL_Rect){0,0,0,0};

    sprite = NULL;

    color.r = randomInt(0, 255);
    color.g = randomInt(0, 255);
    color.b = randomInt(0, 255);

    active = true;

    create_time = SDL_GetTicks();
}

Particle::~Particle()
{
    delete sprite;
}

void Particle::onLoop()
{
    if (active)
    {
        x += Timer::fps.getSpeedFactor(x_vel);
        y += Timer::fps.getSpeedFactor(y_vel);

        x_vel += Timer::fps.getSpeedFactor(x_mod);
        y_vel += Timer::fps.getSpeedFactor(y_mod);

        clip_rect.x = (int)x;
        clip_rect.y = (int)y;

        if (SDL_GetTicks()-create_time >= life_span)
        {
            active = false;
        }
    }
}

Streamer::Streamer()
{
    name = "";
    parent = NULL;

    max_parts = 0;
    spawn_region = (SDL_Rect){0, 0, 0, 0};
    pos.X(0);
    pos.Y(0);

    stream_length = 0;
    start_time = 0;

    spawn_rate = 0;
    last_spawn = 0;

    streamer_list.push_back(this);
}

Streamer::Streamer(string p_name, int x, int y, int w, int h, int num_parts, int sp_time, int stream_time)
{
    parent = (Emitter*)Asset::get(p_name);

    max_parts = num_parts;
    parts.reserve(num_parts);

    pos.X(x);
    pos.Y(y);
    spawn_region = (SDL_Rect) { x, y, w, h};

    stream_length = stream_time;
    start_time = SDL_GetTicks();

    spawn_rate = sp_time;
    last_spawn = SDL_GetTicks();

    streamer_list.push_back(this);
}

Streamer::~Streamer()
{
    parts.clear();
}

Streamer* Streamer::getStreamer(string s_name)
{
    for (int i = 0; i < streamer_list.size(); i++)
    {
        if (s_name == streamer_list[i]->getName())
        {
            return streamer_list[i];
        }
    }

    return NULL;
}

void Streamer::stopStream()
{
    parts.clear();
    stream_length = 0;
}

void Streamer::onBurst(int num_parts)
{
    for (int i = 0; i < num_parts; i++)
    {
        createParticle();
    }
}

void Streamer::onStream(int num_parts, int sp_time, int stream_time)
{
    spawn_rate = sp_time;
    stream_length = stream_time;

    if (num_parts != max_parts)
    {
        max_parts = num_parts;

        parts.clear();
        parts.reserve(num_parts);
    }

    start_time = SDL_GetTicks();
}

void Streamer::onLoop()
{
    if (pos.isAnchored())
    {
        X(pos.Anchor()->X()+pos.offX());
        Y(pos.Anchor()->Y()+pos.offY());
    }
    if (stream_length < 0 || SDL_GetTicks() - start_time < stream_length)
    {
        int dif_time = SDL_GetTicks()-last_spawn;
        if (dif_time >= spawn_rate)
        {
            while(dif_time >= spawn_rate)
            {
                if (parts.size() < max_parts)
                {
                    createParticle();
                }
                else
                {
                    for (int i = 0; i < parts.size(); i++)
                    {
                        if (!parts[i]->active)
                        {
                            resetParticle(parts[i]);
                            break;
                        }
                    }
                }

                dif_time -= spawn_rate;
            }
            last_spawn = SDL_GetTicks();
        }
    }
    else
    {
        parts.clear();
    }

    for (int i = 0; i < parts.size(); i++)
    {
        parts[i]->onLoop();
    }
}

bool Streamer::createParticle()
{
    Particle *tmp = new Particle;

    if (!parent)
    {
        Log::game_log->pushError("Corrupted Steamer!");
        delete tmp;
        return false;
    }

    tmp->clip_rect.x = randomInt(spawn_region.x, spawn_region.x+spawn_region.w);
    tmp->clip_rect.y = randomInt(spawn_region.y, spawn_region.y+spawn_region.h);

    tmp->clip_rect.w = randomInt(parent->getMinWidth(), parent->getMaxWidth());
    tmp->clip_rect.h = randomInt(parent->getMinHeight(), parent->getMaxHeight());

    tmp->x = tmp->clip_rect.x;
    tmp->y = tmp->clip_rect.y;

    tmp->life_span = randomInt(parent->getMinLife(), parent->getMaxLife());

    tmp->x_vel = randomFloat(parent->getMinXVelocity(), parent->getMaxXVelocity());
    tmp->y_vel = randomFloat(parent->getMinYVelocity(), parent->getMaxYVelocity());

    tmp->x_mod = randomFloat(parent->getMinXMod(), parent->getMaxXMod());
    tmp->y_mod = randomFloat(parent->getMinYMod(), parent->getMaxYMod());

    if (parent->getParticleSprite())
        tmp->sprite = new Sprite(*parent->getParticleSprite());

    tmp->color.r = randomInt(parent->getMinRed(), parent->getMaxRed());
    tmp->color.g = randomInt(parent->getMinGreen(), parent->getMaxGreen());
    tmp->color.b = randomInt(parent->getMinBlue(), parent->getMaxBlue());

    tmp->active = true;
    tmp->create_time = SDL_GetTicks();

    parts.push_back(tmp);

    return true;
}

bool Streamer::resetParticle(Particle *tmp)
{
    if (!parent)
    {
        Log::game_log->pushError("Corrupted Streamer!");
        return false;
    }

    tmp->clip_rect.x = randomInt(spawn_region.x, spawn_region.x+spawn_region.w);
    tmp->clip_rect.y = randomInt(spawn_region.y, spawn_region.y+spawn_region.h);
    tmp->clip_rect.w = randomInt(parent->getMinWidth(), parent->getMaxWidth());
    tmp->clip_rect.h = randomInt(parent->getMinHeight(), parent->getMaxHeight());

    tmp->x = tmp->clip_rect.x;
    tmp->y = tmp->clip_rect.y;

    tmp->life_span = randomInt(parent->getMinLife(), parent->getMaxLife());

    tmp->x_vel = randomFloat(parent->getMinXVelocity(), parent->getMaxXVelocity());
    tmp->y_vel = randomFloat(parent->getMinYVelocity(), parent->getMaxYVelocity());

    tmp->x_mod = randomFloat(parent->getMinXMod(), parent->getMaxXMod());
    tmp->y_mod = randomFloat(parent->getMinYMod(), parent->getMaxYMod());

    if (!tmp->sprite && parent->getParticleSprite())
        tmp->sprite = new Sprite(*parent->getParticleSprite());

    tmp->color.r = randomInt(parent->getMinRed(), parent->getMaxRed());
    tmp->color.g = randomInt(parent->getMinGreen(), parent->getMaxGreen());
    tmp->color.b = randomInt(parent->getMinBlue(), parent->getMaxBlue());

    tmp->active = true;

    tmp->create_time = SDL_GetTicks();
}

Emitter::Emitter()
{
   particle_sprite = NULL;

    min_col.r = min_col.g = min_col.b = 0;
    max_col.r = max_col.g = max_col.b = 255;

    min_x_vel = max_x_vel = 0.0f;
    min_y_vel = max_y_vel = 0.0f;

    min_width = max_width = 0;
    min_height = max_height = 0;

    min_life = max_life = 0;
}

bool Emitter::onLoad(string f_name)
{
    DataFile em_loader;

    if (!em_loader.loadFile(part_path+f_name+part_exten))
    {
        Log::game_log->pushError("Could not find Emitter file: " + f_name);
        return false;
    }

    string em_name;

    int min_r, max_r;
    int min_g, max_g;
    int min_b, max_b;

    int em_m_life, em_mx_life;
    float em_m_xv, em_mx_xv;
    float em_m_yv, em_mx_yv;
    float em_m_xm, em_mx_xm;
    float em_m_ym, em_mx_ym;
    int em_m_w, em_mx_w;
    int em_m_h, em_mx_h;

    for (int i = 0; i < em_loader.numSections(); i++)
    {
        if (em_loader.getSectionName(i) == "Emitter")
        {
            if (!em_loader.getMember(i, "name", &em_name))
            {
                Log::game_log->pushError("Emitter Name not set...using default");
            }

            if (!em_loader.getMember(i, "min_life", &em_m_life))
            {
                Log::game_log->pushError("Emitter Minimum Life value not set...using default");
                em_m_life = 0;
            }

            if (!em_loader.getMember(i, "max_life", &em_mx_life))
            {
                Log::game_log->pushError("Emitter Maximum Life value not set...using default");
                em_mx_life = 100;
            }

            if (!em_loader.getMember(i, "min_x_vel", &em_m_xv))
            {
                Log::game_log->pushError("Emitter minimum x velocity not set...using default");
                em_m_xv = 0;
            }

            if (!em_loader.getMember(i, "max_x_vel", &em_mx_xv))
            {
                Log::game_log->pushError("Emitter maximum x velocity not set...using default");
                em_mx_xv = 0;
            }

            if (!em_loader.getMember(i, "min_y_vel", &em_m_yv))
            {
                Log::game_log->pushError("Emitter minimum y velocity not set...using default");
                em_m_yv = -100;
            }

            if (!em_loader.getMember(i, "max_y_vel", &em_mx_yv))
            {
                Log::game_log->pushError("Emitter maximum y velocity not set...using default");
                em_mx_yv = -50;
            }

            if (!em_loader.getMember(i, "min_x_modifier", &em_m_xm))
            {
                Log::game_log->pushError("Emitter minimum x modifier not set..using default");
                em_m_xm = 0.0f;
            }

            if (!em_loader.getMember(i, "max_x_modifier", &em_mx_xm))
            {
                Log::game_log->pushError("Emitter maximum x modifier not set..using default");
                em_mx_xm = 0.0f;
            }

            if (!em_loader.getMember(i, "min_y_modifier", &em_m_ym))
            {
                Log::game_log->pushError("Emitter minimum y modifier not set..using default");
                em_m_ym = 0.0f;
            }

            if (!em_loader.getMember(i, "max_y_modifier", &em_mx_ym))
            {
                Log::game_log->pushError("Emitter maximum y modifier not set..using default");
                em_mx_ym = 0.0f;
            }

            if (!em_loader.getMember(i, "min_width", &em_m_w))
            {
                Log::game_log->pushError("Emitter minimum width not set...using default");
                em_m_w = 2;
            }

            if (!em_loader.getMember(i, "max_width", &em_mx_w))
            {
                Log::game_log->pushError("Emitter maximum width velocity not set...using default");
                em_mx_w = 3;
            }

            if (!em_loader.getMember(i, "min_height", &em_m_h))
            {
                Log::game_log->pushError("Emitter minimum height velocity not set...using default");
                em_m_h = 2;
            }

            if (!em_loader.getMember(i, "max_height", &em_mx_h))
            {
                Log::game_log->pushError("Emitter maximum height velocity not set...using default");
                em_mx_h = 3;
            }

            if (!em_loader.getMember(i, "min_r", &min_r))
            {
                Log::game_log->pushError("Emitter minimum red not set...using default");
                min_r = 110;
            }

            if (!em_loader.getMember(i, "max_r", &max_r))
            {
                Log::game_log->pushError("Emitter maximum red not set...using default");
                max_r = 140;
            }

            if (!em_loader.getMember(i, "min_g", &min_g))
            {
                Log::game_log->pushError("Emitter minimum green not set...using default");
                min_g = 0;
            }

            if (!em_loader.getMember(i, "max_g", &max_g))
            {
                Log::game_log->pushError("Emitter maximum green not set...using default");
                max_g = 0;
            }

            if (!em_loader.getMember(i, "min_b", &min_b))
            {
                Log::game_log->pushError("Emitter minimum blue not set...using default");
                min_b = 110;
            }

            if (!em_loader.getMember(i, "max_b", &max_b))
            {
                Log::game_log->pushError("Emitter maximum blue not set...using default");
                max_b = 140;
            }

            if (Asset::get(em_name))
            {
                Log::game_log->pushError("Emitter already exists!");
                continue;
            }
            else
            {
                Emitter *new_em = new Emitter();
                new_em->Name(em_name);

                new_em->setXVelRange(em_m_xv, em_mx_xv);
                new_em->setYVelRange(em_m_yv, em_mx_yv);
                new_em->setXModRange(em_m_xm, em_mx_xm);
                new_em->setYModRange(em_m_ym, em_mx_ym);
                new_em->setWidthRange(em_m_w, em_mx_w);
                new_em->setHeightRange(em_m_h, em_mx_h);
                new_em->setLifeRange(em_m_life, em_mx_life);

                new_em->setRedRange(min_r, max_r);
                new_em->setGreenRange(min_g, max_g);
                new_em->setBlueRange(min_b, max_b);

                Asset::add(new_em);
            }
        }
    }

    return true;

}

Emitter::~Emitter()
{

}
