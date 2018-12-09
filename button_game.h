#ifndef BUTTON_GAME_H
#define BUTTON_GAME_H

#include <Arduino.h>
#include "config_game.h"

class ButtonGame {
    private:

    public:
        ButtonGame();
        ~ButtonGame();
        void init();
};

extern ButtonGame buttonGame;

#endif // BUTTON_GAME_H
