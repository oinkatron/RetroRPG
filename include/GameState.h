#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SDL/SDL.h>
#include <map>
#include <string>

#include "GameEvent.h"

#include "Alarm.h"
#include "Graphics.h"
#include "Timer.h"
#include "Image.h"
#include "Object.h"
#include "Sprite.h"
#include "Log.h"
#include "Emitter.h"

#include "Panel.h"
#include "PopupPanel.h"
#include "Tooltip.h"
#include "Button.h"
#include "TextBox.h"
#include "CheckBox.h"
#include "DropDownBox.h"

using namespace std;

class GameState
{
    public:
        virtual ~GameState();

        virtual void onEvent(GameEvent *ge)=0;
        virtual void onLoop()=0;
        virtual void onDraw(Graphics &g)=0;

        virtual void onLoad()=0;
        virtual void onUnload()=0;

        static vector<GameState*> state_stack;
        static bool state_change;

        static void pushState(GameState* s) { state_stack.push_back(s); state_stack[state_stack.size()-1]->onLoad(); state_change = true; Panel::focused_panel = NULL; }
        static void popState() { state_stack[state_stack.size()-1]->onUnload(); state_stack.pop_back(); state_change = true; Panel::focused_panel = NULL; }

    protected:
        GameState();
    private:
};

#endif // GAMESTATE_H
