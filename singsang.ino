#include <M5Core2.h>

#include "src/gui.hpp"

singsang::CGui gui;

void setup()
{
    gui.begin();
}

void loop()
{
    gui.loop();
}

void audio_info(const char *info)
{
    Serial.print("info        ");
    Serial.println(info);
}

void audio_id3data(const char *info)
{
    Serial.print("id3data     ");
    Serial.println(info);
}