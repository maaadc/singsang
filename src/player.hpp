#ifndef SINGSANG_PLAYER_HPP
#define SINGSANG_PLAYER_HPP

#include <Audio.h>
#include <M5Core2.h>
#include <SD.h>
#include <WiFi.h>

#include <memory>
#include <vector>

#include "battery_widget.hpp"
#include "file_selection_widget.hpp"
#include "next_song_widget.hpp"
#include "progress_widget.hpp"
#include "volume_display_widget.hpp"
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
    void handleInactivityTimeout();
    void handleTouchEvents();
    void initializeGui();
    void initializeHardware();
    void populateMusicFileList();
    void updateGui();
    void vibrate();

    Audio m_audio{};

    int                 m_currentVolume{0};
    int                 m_activeSongIdx{-1};
    unsigned int        m_turnOffAfterInactiveForMilliSec{5 * 60 * 1000};
    unsigned int        m_lastActivityTimestamp{0};
    std::vector<String> m_songFiles{};

    CBatteryWidget       m_batteryWidget;
    CFileSelectionWidget m_fileSelectionWidget;
    CNextSongWidget      m_nextSongWidget;
    CProgressWidget      m_progressWidget;
    CVolumeDisplayWidget m_volumeDisplayWidget;
    CVolumeDownWidget    m_volumeDownWidget;
    CVolumeUpWidget      m_volumeUpWidget;
};

}  // namespace singsang

#endif  // SINGSANG_PLAYER_HPP