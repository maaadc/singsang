#include <M5Core2.h>
#include <SD.h>
#include <WiFi.h>

#include "src/SingSangPlayer.hpp"

void setup()
{
    M5.begin();
    //M5.Axp.SetLed(0U);

    WiFi.mode(WIFI_OFF);
    delay(500);

    M5.Lcd.setTextFont(2);
    M5.Lcd.println("Hello, sing sang.");
    //M5.Lcd.drawPngFile(SD, "/logo.png", 0, 0, 120, 120, 0, 0, 120./512.);

    //delay(1000);

    singsang.setVolume(0.3);
    singsang.playMp3("/test2.mp3");
}

void loop()
{
    singsang.loopPlay();
}