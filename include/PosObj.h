#ifndef POSOBJ_H
#define POSOBJ_H

#include "Vector2D.h"


class PosObj
{
    public:
        PosObj();
        virtual ~PosObj();

        static int distance(PosObj *a, PosObj *b) { return sqrt(((b->X()-a->X())*(b->X()-a->X())) + ((b->Y()-a->Y())*(b->Y()-a->Y()))); }
        static int distanceSqrd(PosObj *a, PosObj *b) { return ((b->X()-a->X())*(b->X()-a->X())) + ((b->Y()-a->Y())*(b->Y()-a->Y())); }

        void Anchor(PosObj  *p);
        void Anchor(PosObj *p, float x_off, float y_off);
        PosObj* Anchor() { return fllw; }
        bool isAnchored() { return (fllw); }

        void X(float val) { old_pos.x = pos.x; pos.x = val; }
        void Y(float val) { old_pos.y = pos.y; pos.y = val; }
        float X() { return pos.x; }
        float Y() { return pos.y; }
        float oldX() { return old_pos.x; }
        float oldY() { return old_pos.y; }

        float offX() { return fllw_offset.x; }
        float offY() { return fllw_offset.y; }

    protected:
    private:
        Vector2D pos;
        Vector2D old_pos;
        PosObj *fllw;
        Vector2D fllw_offset;
};

#endif // POSOBJ_H
