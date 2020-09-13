#include <M5Core2.h>
#include <SD.h>
#include <WiFi.h>

#include "Audio.h"
Audio audio;

//#include "src/SingSangPlayer.hpp"

void setup()
{
    M5.begin();
    M5.Axp.SetLed(false);
    M5.Axp.SetSpkEnable(true);

    WiFi.mode(WIFI_OFF);
    delay(500);

    M5.Lcd.setTextFont(2);
    M5.Lcd.println("Hello, sing sang.");
    //M5.Lcd.drawPngFile(SD, "/logo.png", 0, 0, 120, 120, 0, 0, 120./512.);

    //delay(1000);
    audio.setPinout(12, 0, 2);

    audio.setVolume(5);

    audio.connecttoSD("test3.mp3");
    singsang.setVolume(0.3);
    singsang.playMp3("/test2.mp3");
}

void loop()
{
    audio.loop();
}

void audio_info(const char *info)
{
    Serial.print("info        ");
    Serial.println(info);
}

void audio_id3data(const char *info)
{ //id3 metadata
    Serial.print("id3data     ");
    Serial.println(info);
}

void audio_eof_mp3(const char *info)
{ //end of file
    Serial.print("eof_mp3     ");
    Serial.println(info);
}
