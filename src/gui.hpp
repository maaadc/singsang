#ifndef SINGSANG_GUI_HPP
#define SINGSANG_GUI_HPP

#include <M5Core2.h>

#include <map>
#include <memory>
#include <vector>

#include "mode.hpp"
#include "player.hpp"
#include "widgets/base_widget.hpp"

namespace singsang
{
class CGui
{
public:
    CGui() = default;

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