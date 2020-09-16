#include <M5Core2.h>

#include "src/CPlayer.hpp"
#include "src/CGui.hpp"

singsang::CPlayer player;
singsang::CGui gui;

void setup()
{
    M5.begin();
    player.begin();
    gui.begin();

    player.startNextSong();
}

void loop()
{
    player.loop();

    if (audio.isRunning() && audio.getAudioFileDuration() > 0)
    {
        const uint8_t progressPercentage = 100. * audio.getAudioCurrentTime() / audio.getAudioFileDuration();
        gui.drawAudioProgressBar(60, 225, 200, 10, progressPercentage);
    }
    else
    {
        gui.drawAudioProgressBar(60, 225, 200, 10, 0);
    }

    if (M5.Touch.ispressed())
    {
        const auto touchPoint = M5.Touch.getPressPoint();
        Serial.print("x,y = "); Serial.print(touchPoint.x);
        Serial.print(","); Serial.print(touchPoint.y);
        Serial.println("");

        // volume up & down
        if (touchPoint.x < 80 && touchPoint.y < 120)
        {
            player.increaseVolume();
            gui.vibrate();
            // update volume status
        }
        if (touchPoint.x < 80 && touchPoint.y > 120)
        {
            player.decreaseVolume();
            gui.vibrate();
            // update volume status
        }

        // next track
        if (touchPoint.x > 270 && touchPoint.y > 120)
        {
            player.startNextSong();
            gui.vibrate();
        }

        // todo: add dead time after a single click event!
        // react with vibration on gui event???
    }

    //gui.drawBatteryWidget(270, 40, 40, 40);
    // note: this breaks mp3 replay since drawing the png on each cycle takes too much time.
    // need to do the audio processing on the 2nd core.
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