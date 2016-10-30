#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "GameState.h"
#include "PlayState.h"
#include "EditState.h"

class MenuState : public GameState
{
    public:
        virtual ~MenuState();

        static MenuState menu_state;

        void onEvent(GameEvent *ge);
        void onLoad();
        void onLoop();
        void onUnload();
        void onDraw(Graphics &g);
    protected:
        MenuState();
    private:
        SDL_Rect clip;

        Panel *win;
        Button *n_game, *e_game;
        TextBox *box;
        CheckBox *c_box, *lol_box, *idk_box;
        Label *c_box_lbl, *lol_box_lbl, *idk_box_lbl;
        DropDownBox *dd_box;
};

#endif // MENUSTATE_H
