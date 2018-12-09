#ifndef WIFI_GAME_H
#define WIFI_GAME_H

#include <Arduino.h>
#include "config_game.h"

class WifiGame {
    private:

    public:
        WifiGame();
        ~WifiGame();
        void init();
};

extern WifiGame wifiGame;

#endif // WIFI_GAME_H
