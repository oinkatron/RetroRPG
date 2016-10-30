#ifndef OBJECT_H
#define OBJECT_H

#include <SDL/SDL.h>
#include <string>
#include <map>

#include "Log.h"
#include "Timer.h"
#include "Map.h"
#include "Vector2D.h"
#include "PosObj.h"
#include "Sprite.h"
#include "GameEvent.h"

using namespace std;

class ControlScheme
{
    public:
        ControlScheme()
        {
            up_dir = SDLK_UNKNOWN;
            down_dir = SDLK_UNKNOWN;
            left_dir = SDLK_UNKNOWN;
            right_dir = SDLK_UNKNOWN;
            action_a = SDLK_UNKNOWN;
            action_b = SDLK_UNKNOWN;
            action_c = SDLK_UNKNOWN;

            up_p = down_p = left_p = right_p = false;
            a_p = b_p = c_p = false;
        }
        virtual ~ControlScheme()
        {

        }

        SDLKey upKey() { return up_dir; }
        void upKey(SDLKey val) { up_dir = val; }

        SDLKey downKey() { return down_dir; }
        void downKey(SDLKey val) { down_dir = val; }

        SDLKey leftKey() { return left_dir; }
        void leftKey(SDLKey val) { left_dir = val; }

        SDLKey rightKey() { return right_dir; }
        void rightKey(SDLKey val) { right_dir = val; }

        SDLKey actionA() { return action_a; }
        void actionA(SDLKey val) { action_a = val; }

        SDLKey actionB() { return action_b; }
        void actionB(SDLKey  val) { action_b = val; }

        SDLKey actionC() { return action_c; }
        void actionC(SDLKey val) { action_c = val; }

        bool upPressed() { return up_p; }
        void upPressed(bool val) { up_p = val; }

        bool downPressed() { return down_p; }
        void downPressed(bool val) { down_p = val; }

        bool leftPressed() { return left_p; }
        void leftPressed(bool val) { left_p = val; }

        bool rightPressed() { return right_p; }
        void rightPressed(bool val) { right_p = val; }

        bool aPressed() { return a_p; }
        void aPressed(bool val) { a_p = val; }

        bool bPressed() { return b_p; }
        void bPressed(bool val) { b_p = val; }

        bool cPressed() { return c_p; }
        void cPressed(bool val) { c_p = val; }

    private:
        SDLKey up_dir, down_dir, left_dir, right_dir;
        SDLKey action_a, action_b, action_c;

        bool up_p, down_p, left_p, right_p;
        bool a_p, b_p, c_p;
};


class Object
{
    public:
        Object();
        Object(string name);
        virtual ~Object();

        virtual void onExitMap();
        virtual void onLoop();
        virtual void onCollision(Object *other, Tile *t);
        virtual void handleKeyInput(SDLKey key, bool pressed);
        void onMove();
        bool posValid(int x, int y);
        bool objValid(Object *b);
        bool mapValid(Tile *t);

        string Name() { return name; }

        int UID() { return u_id; }

        //getters and setters

        Sprite *sprite() { return cur_sprite; }
        void sprite(Sprite *val);
        void sprite(string name);

        PosObj* getPosition() { return pos; }
        void setPosition(float nx, float ny) { pos->X(nx); pos->Y(ny); box.x = (int)nx - (box.w/2); box.y = (int)ny - (box.h/2); }

        float X() { return pos->X(); }
        void X(float val) { pos->X(val); box.x = (int)pos->X() - (box.w/2); }

        float Y() { return pos->Y(); }
        void Y(float val) { pos->Y(val); box.y = (int)pos->Y() - box.h/2; }

        int mapX() { if (local) return (int)pos->X() / local->tileSize(); else return -1; }
        int mapY() { if (local) return (int)pos->Y() / local->tileSize(); else return -1; }


        float startX() { return start_pos.x; }
        void startX(float val) { start_pos.x = val; }

        float startY() { return start_pos.y; }
        void startY(float val) { start_pos.y = val; }

        int boxX() { return box.x; }
        int boxY() { return box.y; }

        int W() { return box.w; }
        void W(int val) { box.w = val; }

        int H() { return box.h; }
        void H(int val) { box.h = val; }

        int xOrigin() { return origin_offset.x; }
        void xOrigin(int val) { origin_offset.x = val;}

        int yOrigin() { return origin_offset.y; }
        void yOrigin(int val) { origin_offset.y = val;}

        float xVel() { return vel.x; }
        void xVel(float val) { vel.x = val; }

        float yVel() { return vel.y; }
        void yVel(float val) { vel.y = val; }

        Vector2D& Velocity() { return vel; }

        float xAccel() { return accel.x; }
        void xAccel(float val) { accel.x = val; }

        float yAccel() { return accel.y; }
        void yAccel(float val) { accel.y = val; }

        Vector2D& Acceleration() { return accel; }

        float maxVel() { return max_vel; }
        void maxVel(float val) { max_vel = val; }

        bool canMove() { return can_move; }
        void canMove(bool val) { can_move = val; }

        bool canJump() { return can_jump; }

        bool Soild() { return solid; }
        void Solid(bool val) { solid = val; }

        bool Ghost() { return ghost; }
        void Ghost(bool val) { ghost = val; }

        bool Gravity() { return gravity; }
        void Gravity (bool val ) { gravity = val; }

        bool isAnchored() { return anchored; }
        Object *getAnchoredObj() { return anchored_obj; }

        void anchor(Object *a_obj);

        ControlScheme& Controls() { return controls; }
        void Controls(ControlScheme val) { controls = val; }

        Map* Local() { return local; }
        void Local(Map* val) { local = val;}

        int Depth() { return depth; }
        void Depth(int val) { depth = val; }

        SDL_Rect& getBounds() { return box; }

        //STATIC MEMBERS
        static int obj_id;
        static int next_id;
        static map<string, Object*> obj_bank;
        static map<string, Object*>::iterator obj_it;

        static bool checkCollision(Object &a, Object &b);
        static bool checkRects(SDL_Rect& a, SDL_Rect& b);
        static bool isInside(int x, int y, Object &a);
        static vector<Object*> getObjectsInRect(SDL_Rect r);
        static vector<Object*> getObjectsInRect(int x, int y, int w, int h);

        static Object* getObject(string name);
        static Object* getObject(int id);

        static void purge(string name);
        static void purge(Object* o);
        static void purge();

    protected:
        ControlScheme controls;

        string name;
        int u_id;

        Sprite *cur_sprite;

        SDL_Rect box;
        PosObj *pos;
        Vector2D start_pos;
        Vector2D vel;
        Vector2D accel;
        Vector2D origin_offset;

        float max_vel;

        bool solid;
        bool ghost;
        bool gravity;
        bool can_move;

        bool moving_left;
        bool moving_right;
        bool moving_up;
        bool moving_down;

        bool anchored;
        Vector2D anchor_offset;
        Object *anchored_obj;

        bool can_jump;

        Map *local;

        int depth;
    private:

};

class ObjectCollision
{
    public:
        ObjectCollision()
        {
            a = NULL;
            b = NULL;
            t = NULL;
        }
        static vector<ObjectCollision*> col_list;
        static void add(ObjectCollision *a);

        Object *a, *b;
        Tile *t;

    protected:
    private:
};

#endif // OBJECT_H
