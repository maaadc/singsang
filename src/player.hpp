#ifndef SINGSANG_PLAYER_HPP
#define SINGSANG_PLAYER_HPP

#include <Audio.h>
#include <M5Core2.h>
#include <SD.h>
#include <WiFi.h>

#include <memory>
#include <vector>

#include "file_selection_widget.hpp"
#include "next_song_widget.hpp"
#include "progress_widget.hpp"
#include "volume_down_widget.hpp"
#include "volume_up_widget.hpp"

namespace singsang
{
class CPlayer
{
public:
    CPlayer();

    ~CPlayer() = default;

    void begin();

    void loop();

    void startNextSong();

    void updateVolume(int f_deltaVolume);

    void increaseVolume();

    void decreaseVolume();

private:
    void handleTouchEvents();
    void initializeGui();
    void initializeHardware();
    void populateMusicFileList();
    void updateGui();
    void vibrate();

    Audio m_audio{};

    int m_currentVolume{0};
    int m_activeSongIdx{-1};
    std::vector<String> m_songFiles{};

    CFileSelectionWidget m_fileSelectionWidget;
    CNextSongWidget m_nextSongWidget;
    CProgressWidget m_progressWidget;
    CVolumeDownWidget m_volumeDownWidget;
    CVolumeUpWidget m_volumeUpWidget;
};

}  // namespace singsang

#endif  // SINGSANG_PLAYER_HPP