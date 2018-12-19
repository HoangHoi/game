#ifndef GAME_H_
#define GAME_H_

#include <Arduino.h>

#define SERIAL_BAUD_RATE 115200

#define LED_PIN D3
#define LED_SIGNAL_ON LOW
#define LED_SIGNAL_OFF HIGH
#define LED_MAX_BLINK_COUNT 100
#define LED_SHORT_TIMEOUT 500
#define LED_LONG_TIMEOUT 1000

#define BUTTON_PIN D4
#define BUTTON_SIGNAL_DOWN HIGH
#define BUTTON_SIGNAL_UP LOW
#define BUTTON_DELAY 10

#define HOST "192.168.2.13"
#define PORT 3000

#define WIFI_SSID "Tang-4"
#define WIFI_PASS "!@#$%^&*o9"
#define WIFI_TIMES_TRY 20

#define WIFI_CONNECT_OK 1
#define WIFI_CONNECT_TIMEOUT 0



#endif
