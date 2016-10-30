#include "../include/GameState.h"

vector<GameState*> GameState::state_stack;
bool GameState::state_change = false;

GameState::GameState()
{

}

GameState::~GameState()
{
    //dtor
}
