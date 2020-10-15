#include "player.hpp"

void audio_id3image(File& audioFile, const int framesize)
{
    // Ensure there is enough heap space
    if (ESP.getFreeHeap() < 1.2 * framesize)
    {
        return;
    }

    std::unique_ptr<char[]> img_p{new char[framesize]};
    const auto              img = img_p.get();

    audioFile.readBytes(img, framesize);

    // A valid jpeg file starts with the hex code "FF D8 FF" and ends with "FF
    // D9". Extract position of the file start
    size_t ofs         = 0;
    bool   isJpegBegin = false;
    for (ofs = 0; (!isJpegBegin && ofs + 3 < framesize); ofs++)
    {
        isJpegBegin = (img[ofs + 1] == 0xFF && img[ofs + 2] == 0xD8 &&
                       img[ofs + 3] == 0xFF);
    }
    if (isJpegBegin)
    {
        M5.Lcd.drawJpg((uint8_t*)(img + ofs),
                       static_cast<size_t>(framesize - ofs), 60, 20, 200, 200,
                       0, 0, JPEG_DIV_2);
    }
}

namespace singsang
{
void CPlayer::begin()
{
    initializeHardware();
    vibrate();
}

void CPlayer::loop()
{
    m_audio.loop();
}

void CPlayer::initializeHardware()
{
    M5.begin();

    WiFi.mode(WIFI_OFF);
    delay(100);

    M5.Axp.SetLed(false);
    M5.Axp.SetLcdVoltage(2700);  // dimmed, nominal value is 2800
    M5.Axp.SetSpkEnable(true);

    m_audio.setPinout(12, 0, 2);
    m_audio.setVolume(0);

    populateMusicFileList();
}

void CPlayer::populateMusicFileList()
{
    File musicDir = SD.open("/music");

    bool nextFileFound;
    do
    {
        nextFileFound = false;

        File entry = musicDir.openNextFile();

        if (entry)
        {
            nextFileFound = true;

            const bool entryIsFile = (entry.size() > 0);
            if (entryIsFile)
            {
                m_songFiles.push_back(entry.name());
            }

            entry.close();
        }
    } while (nextFileFound);

    Serial.print("MusicFileList length: ");
    Serial.println(m_songFiles.size());
}

void CPlayer::startNextSong()
{
    if (m_songFiles.size() == 0)
    {
        return;
    }

    m_activeSongIdx++;
    if (m_activeSongIdx >= m_songFiles.size() || m_activeSongIdx < 0)
    {
        m_activeSongIdx = 0;
    }

    if (m_audio.isRunning())
    {
        m_audio.stopSong();
    }

    m_audio.connecttoSD(m_songFiles[m_activeSongIdx]);
}

void CPlayer::updateVolume(int f_deltaVolume)
{
    constexpr int minVolume = 0;
    constexpr int maxVolume = 16;

    int newVolume = m_currentVolume + f_deltaVolume;

    if (newVolume < minVolume)
    {
        newVolume = minVolume;
    }
    if (newVolume > maxVolume)
    {
        newVolume = maxVolume;
    }

    m_currentVolume = newVolume;
    m_audio.setVolume(m_currentVolume);
}

void CPlayer::increaseVolume()
{
    updateVolume(+4);
}

void CPlayer::decreaseVolume()
{
    updateVolume(-4);
}

void CPlayer::vibrate()
{
    M5.Axp.SetLDOEnable(3, true);
    delay(150);
    M5.Axp.SetLDOEnable(3, false);
}

}  // namespace singsang