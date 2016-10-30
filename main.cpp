#include "include/GameInstance.h"
#include <ctime>
#include <cstdlib>

int main ( int argc, char** argv )
{
    //init random num genorator
    srand((unsigned)time(0));

    GameInstance the_game;

    if (the_game.init())
        the_game.onLoop();

    return 0;
}
