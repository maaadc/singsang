#include <M5Core2.h>

#include "src/player.hpp"

singsang::CPlayer player;

void setup()
{
    player.begin();
}

void loop()
{
    player.loop();
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