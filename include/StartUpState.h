#ifndef STARTUPSTATE_H
#define STARTUPSTATE_H

#include "GameState.h"


class StartUpState : public GameState
{
    public:
        StartUpState();
        virtual ~StartUpState();

        static StartUpState start_state;
        static void nextState();

        void onLoop();
        void onEvent(GameEvent *ge);
        void onDraw(Graphics &g);
        void onLoad();
        void onUnload();

    protected:
    private:
};

#endif // STARTUPSTATE_H
