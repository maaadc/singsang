#include "player.hpp"

#include "helpers.hpp"

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

    // A valid jpeg file starts with the hex code "FF D8 FF" and ends with "FF D9".
    // Extract position of the file start.
    size_t ofs         = 0;
    bool   isJpegBegin = false;
    for (ofs = 0; (!isJpegBegin && ofs + 3 < framesize); ofs++)
    {
        isJpegBegin = (img[ofs + 1] == 0xFF && img[ofs + 2] == 0xD8 && img[ofs + 3] == 0xFF);
    }
    if (isJpegBegin)
    {
        M5.Lcd.drawJpg((uint8_t*)(img + ofs), static_cast<size_t>(framesize - ofs), 60, 20, 200, 200);
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
    setVolume(8);

    populateMusicStorage();
}

void CPlayer::addFilesInCategory(songList_t& f_songs, File& f_musicDir)
{
    bool nextFileFound{};
    do
    {
        File entry    = f_musicDir.openNextFile();
        nextFileFound = static_cast<bool>(entry);

        if (entry)
        {
            const String fileName = entry.name();

            const bool entryIsMp3File = (entry.size() > 0) && fileName.endsWith("mp3");
            if (entryIsMp3File)
            {
                f_songs.push_back(fileName);

                Serial.print("  mp3  ");
                Serial.println(fileName);
            }

            entry.close();
        }
    } while (nextFileFound);
}

void CPlayer::populateMusicStorage()
{
    File musicDir = SD.open("/music");

    bool nextFileFound;
    do
    {
        File entry    = musicDir.openNextFile();
        nextFileFound = static_cast<bool>(entry);

        if (entry && entry.isDirectory())
        {
            const String iconFilePath       = String(entry.name()) + "/folder.jpg";
            const bool   isValidMusicFolder = SD.exists(iconFilePath);

            if (isValidMusicFolder)
            {
                Serial.println("Category: ");
                Serial.print("  icon ");
                Serial.println(iconFilePath);

                categoryList_t newCategory{};
                newCategory.first = iconFilePath;
                addFilesInCategory(newCategory.second, entry);
                m_songs.push_back(newCategory);
            }
            entry.close();
        }
    } while (nextFileFound);

    Serial.print("Found ");
    Serial.print(m_songs.size());
    Serial.println(" categories.");
}

void CPlayer::selectNextCategory()
{
    if (m_songs.size() == 0)
    {
        return;
    }

    m_activeCategoryIdx++;
    if (m_activeCategoryIdx >= m_songs.size() || m_activeCategoryIdx < 0)
    {
        m_activeCategoryIdx = 0;
    }

    m_activeSongIdx = 0;
    updateCategoryIcon(EGuiMode::CategoryView);
}

void CPlayer::selectNextSong()
{
    auto& files = m_songs[m_activeCategoryIdx].second;

    if (files.size() == 0)
    {
        return;
    }

    m_activeSongIdx++;
    if (m_activeSongIdx >= files.size() || m_activeSongIdx < 0)
    {
        m_activeSongIdx = 0;
    }
}

void CPlayer::togglePlayPause()
{
    if (m_audio.isRunning())
    {
        m_audio.stopSong();
    }
    else
    {
        playSelectedSong();
    }
}

void CPlayer::setVolume(int f_newVolume)
{
    m_currentVolume = clip(m_minVolume, f_newVolume, m_maxVolume);
    m_audio.setVolume(m_currentVolume);
}

void CPlayer::decreaseVolume()
{
    setVolume(m_currentVolume - 4);
}

void CPlayer::increaseVolume()
{
    setVolume(m_currentVolume + 4);
}

void CPlayer::updateCategoryIcon(EGuiMode f_mode)
{
    if (f_mode == EGuiMode::StartupView)
    {
        M5.Lcd.drawJpgFile(SD, "/media/logo.jpg", 60, 20, 200, 200);
    }
    if (f_mode == EGuiMode::CategoryView)
    {
        char fileName[128] = "";
        m_songs[m_activeCategoryIdx].first.toCharArray(fileName, 128U);
        M5.Lcd.drawJpgFile(SD, fileName, 60, 20, 200, 200);
    }
}

void CPlayer::switchToMode(EGuiMode& f_mode, EGuiMode f_newMode)
{
    vibrate();

    if (f_mode == EGuiMode::StartupView && f_newMode == EGuiMode::CategoryView)
    {
        updateCategoryIcon(f_newMode);
    }

    if (f_mode == EGuiMode::CategoryView && f_newMode == EGuiMode::SongView)
    {
        playSelectedSong();
    }

    if (f_mode == EGuiMode::SongView && f_newMode == EGuiMode::CategoryView)
    {
        stopReplay();
        updateCategoryIcon(f_newMode);
    }

    if (f_mode == EGuiMode::CategoryView && f_newMode == EGuiMode::StartupView)
    {
        updateCategoryIcon(f_newMode);
    }

    f_mode = f_newMode;
}

void CPlayer::vibrate()
{
    M5.Axp.SetLDOEnable(3, true);
    delay(150);
    M5.Axp.SetLDOEnable(3, false);
}

}  // namespace singsang