#include "button_game.h"

/**
 * constructor
 */
ButtonGame::ButtonGame()
{
    // EEPROM.begin(EEPROM_SIZE);
}

/**
 * destructor
 */
ButtonGame::~ButtonGame()
{
}

void ButtonGame::init()
{
    pinMode(BUTTON_PIN, INPUT);
}

ButtonGame buttonGame;
