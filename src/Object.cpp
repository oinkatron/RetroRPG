#include "../include/Object.h"

int Object::next_id = 0;
int Object::obj_id = 0;
map<string, Object*> Object::obj_bank;
map<string, Object*>::iterator Object::obj_it;
vector<ObjectCollision*> ObjectCollision::col_list;

Object::Object()
{
    pos = new PosObj();
    box = (SDL_Rect){0, 0, 0, 0};
    depth = -1;
    start_pos.setComponents(0.0f, 0.0f);
    vel.setComponents(0.0f, 0.0f);
    accel.setComponents(0.0f, 0.0f);
    origin_offset.setComponents(0.0f, 0.0f);

    anchor_offset.setComponents(0.0f, 0.0f);
    anchored = false;
    anchored_obj = NULL;

    max_vel = 200.0f;

    u_id = next_id++;
    name = "Object_"+toString(u_id);

    solid = false;
    can_move = false;

    moving_down = false;
    moving_left = false;
    moving_right = false;
    moving_up = false;
    can_jump = false;

    local = NULL;
    cur_sprite = NULL;

    obj_bank.insert(pair<string, Object*>(name, this));
}

Object::Object(string n_name)
{
    pos = new PosObj();
    box = (SDL_Rect){0, 0, 0, 0};
    start_pos.setComponents(0.0f, 0.0f);
    vel.setComponents(0.0f, 0.0f);
    accel.setComponents(0.0f, 0.0f);
    origin_offset.setComponents(0.0f, 0.0f);

    anchor_offset.setComponents(0.0f, 0.0f);
    anchored = false;
    anchored_obj = NULL;

    max_vel = 200.0f;

    u_id = next_id++;
    name = n_name;

    solid = false;
    can_move = false;

    moving_down = false;
    moving_left = false;
    moving_right = false;
    moving_up = false;
    can_jump = false;

    local = NULL;
    cur_sprite = NULL;
    obj_bank.insert(pair<string, Object*>(name, this));
}

Object::~Object()
{
    if (local)
    {
        local = NULL;
    }
    if (cur_sprite)
    {
        delete cur_sprite;
    }
    if (pos)
        delete pos;
}

void Object::purge(string name)
{
    obj_it = obj_bank.find(name);
    if (obj_it == obj_bank.end())
    {
        Log::game_log->pushError("Cannot Delete Object: " + name + ", not found");
        return;
    }

    delete obj_it->second;
    obj_bank.erase(obj_it);
}

void Object::purge(Object* o)
{
    if (!o)
    {
        Log::game_log->pushError("Null object pased cannot delete!");
        return;
    }

    obj_it = obj_bank.find(o->Name());
    if (obj_it != obj_bank.end())
    {
        if (o == obj_it->second)
        {
            delete obj_it->second;
            obj_bank.erase(obj_it);
            return;
        }
    }

    Log::game_log->pushError("Cannot delete, Object: " + o->Name() + " not found!");
    return;
}

void Object::purge()
{
    for (obj_it = obj_bank.begin(); obj_it != obj_bank.end(); obj_it++)
    {
        delete obj_it->second;
    }

    obj_bank.clear();
}

Object* Object::getObject(string name)
{
    obj_it = obj_bank.find(name);
    if (obj_it == obj_bank.end())
    {
        Log::game_log->pushError("Object: " + name + " not found!");
        return NULL;
    }

    return obj_it->second;
}

Object* Object::getObject(int id)
{
    for (obj_it = obj_bank.begin();  obj_it != obj_bank.end(); obj_it++)
    {
        if (obj_it->second->UID() == id)
        {
            return obj_it->second;
        }
    }

    Log::game_log->pushError("Cannot find object with uid: " + id);
    return NULL;
}

void Object::handleKeyInput(SDLKey key, bool pressed)
{

}

void Object::onLoop()
{
    if (accel.x != 0)
    {
        vel.x += accel.x;
        if (vel.x > max_vel)
        {
            vel.x = max_vel;
        }
        else if (vel.x < -max_vel)
        {
            vel.x = -max_vel;
        }
    }
    else
    {
        if (vel.x > 0.3 || vel.x < -0.3)
            vel.x *= 0.85f;
        else
            vel.x = 0;
    }

    if (gravity)
    {
        vel.y += Timer::fps.getSpeedFactor(1500);
    }

    if (accel.y != 0)
    {
        vel.y += accel.y;
        if (vel.y > max_vel)
        {
            vel.y = max_vel;
        }
    }

    if (anchored)
    {
        X(anchored_obj->X() + anchor_offset.x);
        Y(anchored_obj->Y() + anchor_offset.y);
    }
    else
    {
        if (vel.x != 0 || vel.y != 0)
        {
            onMove();
        }
    }


    if (local)
    {
        if (pos->X() + box.w < 0 || pos->X() > local->Width()|| pos->Y() + box.h < 0 || pos->Y() > local->Height())
        {
            onExitMap();
        }
    }
}

void Object::onMove()
{
    if (pos->isAnchored())
    {
        X(pos->Anchor()->X()+pos->offX());
        Y(pos->Anchor()->Y()+pos->offY());
        return;
    }

    Vector2D diff;
    Vector2D step;
    Vector2D moved;
    Vector2D virt_pos;

    diff.x = Timer::fps.getSpeedFactor(vel.x);
    diff.y = Timer::fps.getSpeedFactor(vel.y);

    step = diff;
    step.normalize();
    virt_pos.x = X();
    virt_pos.y = Y();
    moved.setComponents(0, 0);

    int count = 0;

    while (true)
    {
        count ++;
        if (posValid(virt_pos.x + step.x, virt_pos.y))
        {
            virt_pos.x += step.x;
        }
        else
        {
            vel.x = 0.0f;
        }

        if (posValid(virt_pos.x, virt_pos.y + step.y))
        {
            virt_pos.y += step.y;
        }
        else
        {
            vel.y = 0;
        }

        moved.x += step.x;
        moved.y += step.y;

        if (step.x < 0)
        {
            if(moved.x <= diff.x)
            {
                 break;
            }
        }
        else if (step.x > 0)
        {
            if (moved.x >= diff.x)
                break;
        }

        if (step.y < 0)
        {
            if (moved.y <= diff.y)
                break;
        }
        else if (step.y > 0)
        {
            if(moved.y >= diff.y)
                break;
        }
    }
    X(virt_pos.x);
    Y(virt_pos.y);
}

void Object::onCollision(Object* other, Tile *t)
{
    if (other)
    {

    }
    else if (t)
    {

    }
}

bool Object::posValid(int n_x, int n_y)
{
    PosObj old_pos(*pos);
    bool result = true;

    //Store previus location and
    //Move object to where we want to check
    X(n_x);
    Y(n_y);

    if (local)
    {
        int sx = box.x/local->tileSize();
        int sy = box.y/local->tileSize();
        int ex = (box.x + box.w)/local->tileSize();
        int ey = (box.y + box.h)/local->tileSize();

        for (int i = sx; i <= ex; i++)
        {
            for(int ii = sy; ii <= ey; ii++)
            {
                if (mapValid(local->getTile(i, ii)))
                {
                    ObjectCollision *new_col = new ObjectCollision;
                    new_col->a = this;
                    new_col->b = NULL;
                    new_col->t = local->getTile(i, ii);

                    ObjectCollision::add(new_col);
                    result = false;
                }
            }
        }
    }

    map<string, Object*>::iterator map_it;
    for (map_it = obj_bank.begin(); map_it != obj_bank.end(); map_it++)
    {
        if (map_it->second != this)
        {
            if (objValid(map_it->second))
            {
                ObjectCollision *new_col = new ObjectCollision;
                new_col->a = this;
                new_col->b = map_it->second;
                new_col->t = NULL;
                ObjectCollision::add(new_col);

                result = false;
            }
        }
    }

    X(old_pos.X());
    Y(old_pos.Y());

    return result;
}

void Object::sprite(string name)
{
    if (cur_sprite)
    {
        delete cur_sprite;
    }

    cur_sprite = new Sprite((SpriteBase*)Asset::get(name));
}

void Object::sprite(Sprite *val)
{
    if (cur_sprite)
    {
        delete cur_sprite;
    }

    cur_sprite = val;
}

bool Object::mapValid(Tile *t)
{
    if (t != NULL)
    {
        if (t->type == TILE_SOLID)
        {
            return true;
        }
    }
    return false;
}

bool Object::objValid(Object *b)
{
    if (!b)
        return false;

    if (checkCollision(*this, *b))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Object::checkCollision(Object &a, Object &b)
{
    if (a.box.x > b.box.x + b.box.w)
        return false;
    else if (a.box.x + a.box.w < b.box.x)
        return false;
    else if (a.box.y > b.box.y + b.box.h)
        return false;
    else if (a.box.y + a.box.h < b.box.y)
        return false;

    return true;
}

bool Object::checkRects(SDL_Rect& a, SDL_Rect& b)
{
   if (a.x > b.x + b.w)
        return false;
    else if (a.x + a.w < b.x)
        return false;
    else if (a.y > b.y + b.h)
        return false;
    else if (a.y + a.h < b.y)
        return false;

    return true;
}

bool Object::isInside(int x, int y, Object& a)
{
    if (x > a.box.x && x < a.box.x + a.box.w && y > a.box.y && y < a.box.y + a.box.h)
    {
        return true;
    }

    return false;
}

vector<Object*> Object::getObjectsInRect(SDL_Rect r)
{
    Log::game_log->pushLog("Finding objects in rect: " + toString(r.x) + " | " + toString(r.y) + " | " + toString(r.w) + " | " + toString(r.h) + " | ");
    vector<Object*> obj_list;
    for (obj_it = obj_bank.begin(); obj_it != obj_bank.end(); obj_it++)
    {
        if (checkRects(obj_it->second->box, r))
        {
            obj_list.push_back(obj_it->second);
        }
    }

    return obj_list;
}

vector<Object*> Object::getObjectsInRect(int x, int y, int w, int h)
{
    SDL_Rect r = (SDL_Rect){x,y,w,h};
    return getObjectsInRect(r);
}

void Object::onExitMap()
{
    X(start_pos.x);
    Y(start_pos.y);
}

void ObjectCollision::add(ObjectCollision* col)
{
    bool can_add = true;
    if (col_list.size() == 0)
    {
        col_list.push_back(col);
    }
    else
    {
        for (int i = 0; i < col_list.size(); i++)
        {
            if (col_list[i]->a == col->a && col_list[i]->b == col->b && col_list[i]->t == col->t)
            {
                can_add = false;
                break;
            }
        }

        if (can_add)
        {
            col_list.push_back(col);
        }
    }
}
