#include <SocketIOClient.h>
// #include <ArduinoJson.h>
#include "game.h"

SocketIOClient socket;

uint8_t ledState = LED_SIGNAL_OFF;
uint8_t ledBlinkCount = 0;
uint32_t ledBlinkTimeout = 0;
uint32_t ledTimeInterval = LED_SHORT_TIMEOUT;

uint8_t triggered = 0;

int connectWifi(const char* ssid, const char* pass)
{
    Serial.println("[WifiService][connect] Open STA....");
    Serial.print("[WifiService][connect] Wifi connect to: ");
    Serial.println(ssid);
    Serial.print("[WifiService][connect] With pass: ");
    Serial.println(pass);

    WiFi.softAPdisconnect();
    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    delay(100);
    WiFi.begin(ssid, pass);

    int c = 0;
    Serial.println("Waiting for Wifi to connect");
    while (c < WIFI_TIMES_TRY) {
        if (WiFi.status() == WL_CONNECTED) {
            Serial.println("");
            Serial.println("Wifi connected!");
            Serial.print("Local IP: ");
            Serial.println(WiFi.localIP());

            return WIFI_CONNECT_OK;
        }
        delay(WIFI_CONNECT_DELAY);
        Serial.print(".");
        c++;
    }
    Serial.println("");
    Serial.println("Connect timed out");
    return WIFI_CONNECT_TIMEOUT;
}

void emitTrigg() {
    Serial.println("emitTrigg");
    socket.emit("trigg", "1");
}

void setLedBlink(uint8_t blinkCount, uint32_t timeInterval)
{
    Serial.println(blinkCount);
    if (blinkCount > LED_MAX_BLINK_COUNT) {
        blinkCount = LED_MAX_BLINK_COUNT;
    }

    ledBlinkCount = blinkCount * 2;
    ledTimeInterval = timeInterval;
    Serial.println(ledBlinkCount);
    Serial.println(timeInterval);
}

void clearLedBlink()
{
    ledBlinkCount = 0;
    ledState = LED_SIGNAL_OFF;
    digitalWrite(LED_PIN, ledState);
}

void blinkLed()
{
    if (ledBlinkCount) {
        if (millis() > ledBlinkTimeout) {
            ledState = !ledState;
            digitalWrite(LED_PIN, ledState);
            Serial.println(ledState);
            Serial.println(ledBlinkCount);
            ledBlinkCount--;

            ledBlinkTimeout = millis() + ledTimeInterval;
        }
    }
}

void checkButton()
{
    if (triggered) {
        if (digitalRead(BUTTON_PIN) == BUTTON_SIGNAL_UP) {
            Serial.println("digitalRead(BUTTON_PIN) == BUTTON_SIGNAL_UP");
            delay(BUTTON_DELAY);
            if (digitalRead(BUTTON_PIN) == BUTTON_SIGNAL_UP) {
                triggered = 0;
            }
        }
    } else {
        if (digitalRead(BUTTON_PIN) == BUTTON_SIGNAL_DOWN) {

            Serial.println("digitalRead(BUTTON_PIN) == BUTTON_SIGNAL_DOWN");
            delay(BUTTON_DELAY);
            if (digitalRead(BUTTON_PIN) == BUTTON_SIGNAL_DOWN) {
                emitTrigg();
                triggered = 1;
            }
        }
    }
}

void handleWin(String data) {
    Serial.println("[handleWin] " + data);
    setLedBlink(20, LED_SHORT_TIMEOUT);
}

void handleClear(String data) {
    Serial.println("[handleClear] " + data);
    clearLedBlink();
}

void setup() {
    Serial.begin(SERIAL_BAUD_RATE);
    delay(100);
    Serial.println("\nStart up...");
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT);
    digitalWrite(LED_PIN, LED_SIGNAL_ON);
    delay(500);
    digitalWrite(LED_PIN, LED_SIGNAL_OFF);
    delay(500);

    socket.on("win", handleWin);
    socket.on("clear", handleClear);
    socket.connect(HOST, PORT);
}

void loop() {
    blinkLed();
    checkButton();
    if (WiFi.status() == WL_CONNECTED) {
        socket.monitor();
        return;
    }

    connectWifi(WIFI_SSID, WIFI_PASS);
}
