#ifndef SINGSANG_SELECT_WIDGET_HPP
#define SINGSANG_SELECT_WIDGET_HPP

#include "base_widget.hpp"

namespace singsang
{
class CGoSelectWidget : public CBaseWidget
{
public:
    CGoSelectWidget(EGuiMode& f_mode, CPlayer& f_player) : CBaseWidget(f_mode, f_player, 60, 20, 200, 200, -40) {}

    void draw(const bool f_updateOnly)
    {
        // other components draw on this widget
    }

    void touch()
    {
        switch (m_mode)
        {
            case EGuiMode::StartupView:
                m_player.switchToMode(m_mode, EGuiMode::CategoryView);
                break;

            case EGuiMode::CategoryView:
                m_player.switchToMode(m_mode, EGuiMode::SongView);
                break;

            case EGuiMode::SongView:
                break;
        }
    }

    void update() {}
};

}  // namespace singsang

#endif  // SINGSANG_NEXT_SONG_WIDGET_HPP