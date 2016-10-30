#ifndef POPUPPANEL_H
#define POPUPPANEL_H

#include "Panel.h"

class PopupPanel : public Panel
{
    public:
        PopupPanel();
        virtual ~PopupPanel();

        static void addPopup(PopupPanel* p) { popup_list.push_back(p); }
        static void clearPopups() { popup_list.clear(); }

        static vector<PopupPanel*> popup_list;

    protected:
    private:
};

#endif // POPUPPANEL_H
