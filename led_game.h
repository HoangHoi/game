#ifndef LED_GAME_H
#define LED_GAME_H

#include <Arduino.h>
#include "config_game.h"

class LedGame {
    private:

    public:
        LedGame();
        ~LedGame();
        void init();
};

extern LedGame ledGame;

#endif // LED_GAME_H
