#include "game.h"
void setup() {
    Serial.begin(SERIAL_BAUD_RATE);
    Serial.println("\nStart up...");
    buttonGame.init();
    ledGame.init();
    wifiGame.init();
}

void loop() {

}
