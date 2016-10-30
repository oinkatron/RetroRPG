#include "../include/StartUpState.h"

StartUpState StartUpState::start_state;

StartUpState::StartUpState()
{

}

StartUpState::~StartUpState()
{
    //dtor
}

void StartUpState::onLoad()
{
    Image::onLoad("ctlogo.png");
}

void StartUpState::onUnload()
{

}

void StartUpState::onLoop()
{

}

void StartUpState::onDraw(Graphics &g)
{
    g.setColor(0, 0, 0);
    g.drawRect(0, 0, g.getContext()->w, g.getContext()->h);

    Image *tmp = dynamic_cast<Image*>(Image::get("ctlogo.png"));
    g.drawImage(g.getContext()->w/2 - tmp->W()/2, 0, tmp, NULL);
}

void StartUpState::onEvent(GameEvent *ge)
{

}
