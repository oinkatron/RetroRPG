#ifndef DROPDOWNBOX_H
#define DROPDOWNBOX_H

#include "Panel.h"
#include "DropDownList.h"


class DropDownBox : public Panel
{
    public:
        DropDownBox();
        virtual ~DropDownBox();

        void addOption(string opt);
        string getOption();
        string getOption(int i);

        void onClick(PosObj &m_coords);
        void onRelease(PosObj &m_coords);
        void onDraw(Graphics &g);

    protected:
    private:

};

#endif // DROPDOWNBOX_H
