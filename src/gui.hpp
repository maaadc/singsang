#ifndef SINGSANG_GUI_HPP
#define SINGSANG_GUI_HPP

#include <M5Core2.h>

#include <memory>
#include <vector>

#include "player.hpp"
#include "widgets/battery_widget.hpp"
#include "widgets/file_selection_widget.hpp"
#include "widgets/go_back_widget.hpp"
#include "widgets/next_song_widget.hpp"
#include "widgets/progress_widget.hpp"
#include "widgets/volume_display_widget.hpp"
#include "widgets/volume_down_widget.hpp"
#include "widgets/volume_up_widget.hpp"

namespace singsang
{
class CGui
{
public:
    CGui()  = default;
    ~CGui() = default;

    void begin();

    void loop();

private:
    template <typename T>
    void addWidget();
    void handleTouchEvents();
    void initializeGui();
    void updateGui();

    int32_t m_level{0};
    CPlayer m_player{};

    std::vector<std::shared_ptr<CBaseWidget>> m_widgets{};

    /*CBatteryWidget       m_batteryWidget;
    CFileSelectionWidget m_fileSelectionWidget;
    CNextSongWidget      m_nextSongWidget;
    CProgressWidget      m_progressWidget;
    CVolumeDisplayWidget m_volumeDisplayWidget;
    CVolumeDownWidget    m_volumeDownWidget;
    CVolumeUpWidget      m_volumeUpWidget;*/
};
}  // namespace singsang

#endif  // SINGSANG_GUI_HPP