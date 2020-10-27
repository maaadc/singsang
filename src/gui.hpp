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

    CPlayer  m_player{};
    EGuiMode m_mode{EGuiMode::StartupView};

    std::vector<std::shared_ptr<CBaseWidget>> m_widgets{};

};
}  // namespace singsang

#endif  // SINGSANG_GUI_HPP