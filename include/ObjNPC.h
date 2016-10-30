#ifndef OBJNPC_H
#define OBJNPC_H

#include "Object.h"
enum Direction
{
        DIR_UP=0,
        DIR_RIGHT,
        DIR_DOWN,
        DIR_LEFT
};

class ObjNPC : public Object
{
    struct NPC_SpriteSet
    {
        string w_u_spr, w_l_spr, w_r_spr, w_d_spr;
        string u_spr, d_spr, r_spr, l_spr;
    };

    public:
        ObjNPC() : Object() { cur_dir = DIR_DOWN; ch_dir = false; moving = false; }
        ObjNPC(string name) : Object(name) { cur_dir = DIR_DOWN; ch_dir = false; moving = false; }
        virtual ~ObjNPC();

        void onLoop();
        void handleKeyInput(SDLKey key, bool pressed);

        void curDirection(Direction d) { cur_dir = d; }
        Direction curDirection() { return cur_dir; }

        void Moving(bool val) { moving = val; }
        bool Moving() { return moving; }

        void changedDir(bool val) { ch_dir = val; }
        bool changedDir() { return ch_dir; }

        void charName(string str) { char_name = str; }
        string charName() { return char_name; }

        void chatText(string str) { msg_str = str; }
        string chatText() { return msg_str; }

        void chatPortrait(Image *img) { portrait = img; }
        Image *chatPortrait() { return portrait; }

        void chatPortrait(string i) { portrait = (Image*)Image::get(i); }

        void UpSprite(string us) { spr_set.u_spr = us; }
        string UpSprite() { return spr_set.u_spr; }

        void DownSprite(string ds) { spr_set.d_spr = ds; }
        string DownSprite() { return spr_set.d_spr; }

        void LeftSprite(string ls) { spr_set.l_spr = ls; }
        string LeftSprite() { return spr_set.l_spr; }

        void RightSprite(string rs) { spr_set.r_spr = rs; }
        string RightSprite() { return spr_set.r_spr; }

        void WalkUpSprite(string us) { spr_set.w_u_spr = us; }
        string WalkUpSprite() { return spr_set.w_u_spr; }

        void WalkDownSprite(string ds) { spr_set.w_d_spr = ds; }
        string WalkDownSprite() { return spr_set.w_d_spr; }

        void WalkLeftSprite(string ls) { spr_set.w_l_spr = ls; }
        string WalkLeftSprite() { return spr_set.w_l_spr; }

        void WalkRightSprite(string rs) { spr_set.w_r_spr = rs; }
        string WalkRightSprite() { return spr_set.w_r_spr; }


    protected:
        Direction cur_dir;
        NPC_SpriteSet spr_set;
        bool moving;
        bool ch_dir;

        string char_name;
        string msg_str;
        Image *portrait;
    private:

};

#endif // OBJNPC_H
