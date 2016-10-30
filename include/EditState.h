#ifndef EDITSTATE_H
#define EDITSTATE_H

#include "GameState.h"

#include "Panel.h"
#include "Button.h"
#include "Label.h"
#include "TextBox.h"

#include "Map.h"


class EditState : public GameState
{
    public:
        EditState();
        virtual ~EditState();

        static EditState edit_state;

        void onLoad();
        void onUnload();

        void onLoop();
        void onDraw(Graphics &g);
        void onEvent(GameEvent *ge);

    protected:
    private:
        Map   *edit_map;

        Panel *setup_win, *top_bar;
        Panel *win_map_info;
        Button *tp_sv_btn, *tp_ld_btn;
        Button *l_map_btn, *n_map_btn;
        TextBox *map_width_box, *map_height_box, map_name_box, map_tile_size_box;
        Label *map_width_label, *map_height_label, map_name_label, map_tile_size_label;

};

#endif // EDITSTATE_H
