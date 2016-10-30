#ifndef PLAYER_H
#define PLAYER_H

#include "ObjNPC.h"


class Player : public ObjNPC
{
    public:
        Player() : ObjNPC() {}
        Player(string name) :  ObjNPC(name) {}
        virtual ~Player();

        void handleKeyInput(SDLKey key, bool pressed);
        void onLoop();

        static int player_id;
    protected:
    private:

};

#endif // PLAYER_H
