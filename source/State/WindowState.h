#ifndef _WINDOW_STATE_H_
#define _WINDOW_STATE_H_

#include "../Components/Button.h"

class GameManager;

class WindowState { 
public:
    virtual void init(GameManager *gameMan) = 0;
    virtual void pollEvents(GameManager *gameMan) = 0;
    virtual void update(GameManager *gameMan) = 0;
    virtual void draw(GameManager *gameMan) = 0;
};

#endif