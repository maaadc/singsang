#ifndef SINGSANG_PLAYER_HPP
#define SINGSANG_PLAYER_HPP

#include <Audio.h>
#include <M5Core2.h>
#include <SD.h>
#include <WiFi.h>

#include <vector>

#include "mode.hpp"

namespace singsang
{
class CPlayer
{
public:
    using categoryIconFile_t = String;
    using songFile_t         = String;
    using songList_t         = std::vector<songFile_t>;
    using categoryList_t     = std::pair<categoryIconFile_t, songList_t>;
    using fileStorage_t      = std::vector<categoryList_t>;

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

    String getActiveCategoryIcon() const
    {
        return m_songs[m_activeCategoryIdx].first;
    }

    int getNumberOfSongs() const
    {
        return m_songs[m_activeCategoryIdx].second.size();
    }

    int getVolume() const
    {
        return m_currentVolume;
    }

    void decreaseVolume();

    void increaseVolume();

    void setVolume(int f_deltaVolume);

    void playSelectedSong()
    {
        auto& fileName = m_songs[m_activeCategoryIdx].second[m_activeSongIdx];
        m_audio.connecttoSD(fileName);
    }

    void stopReplay()
    {
        if (m_audio.isRunning())
        {
            m_audio.stopSong();
        }
    }

    void selectNextCategory();

    void selectNextSong();

    void updateCategoryIcon(EGuiMode f_mode);

    void switchToMode(EGuiMode& f_mode, EGuiMode f_newMode);

    void togglePlayPause();

    void vibrate();

private:
    void initializeHardware();

    void populateMusicStorage();

    void addFilesInCategory(songList_t& f_songs, File& f_musicDir);

    Audio m_audio{};

    int       m_currentVolume{8};
    const int m_minVolume{0};
    const int m_maxVolume{16};

    // List of audio files per category. Key is the icon's file name
    fileStorage_t m_songs{};

    int m_activeCategoryIdx{};
    int m_activeSongIdx{};
};

}  // namespace singsang

#endif  // SINGSANG_PLAYER_HPP