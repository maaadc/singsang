#ifndef SINGSANG_PLAYER_HPP
#define SINGSANG_PLAYER_HPP

#include <Audio.h>
#include <M5Core2.h>
#include <SD.h>
#include <WiFi.h>

#include <vector>

namespace singsang
{
class CPlayer
{
public:
    CPlayer() = default;

    ~CPlayer() = default;

    void begin();

    void loop();

    inline Audio& getAudio()
    {
        return m_audio;
    }

    void startNextSong();

    int getActiveSongIndex() const
    {
        return m_activeSongIdx;
    }

    int getNumberOfSongs() const
    {
        return m_songFiles.size();
    }

    int getVolume() const
    {
        return m_currentVolume;
    }

    void updateVolume(int f_deltaVolume);

    void increaseVolume();

    void decreaseVolume();

    void vibrate();

private:
    void initializeHardware();
    void populateMusicFileList();

    Audio m_audio{};

    int                 m_currentVolume{0};
    int                 m_activeSongIdx{-1};
    std::vector<String> m_songFiles{};
};

}  // namespace singsang

#endif  // SINGSANG_PLAYER_HPP