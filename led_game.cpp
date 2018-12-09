#include "led_game.h"

/**
 * constructor
 */
LedGame::LedGame()
{
    // EEPROM.begin(EEPROM_SIZE);
}

/**
 * destructor
 */
LedGame::~LedGame()
{
}

void LedGame::init()
{
    pinMode(LED_PIN, OUTPUT);
}

LedGame ledGame;
