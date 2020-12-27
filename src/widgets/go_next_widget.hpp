#ifndef SINGSANG_GO_NEXT_WIDGET_HPP
#define SINGSANG_GO_NEXT_WIDGET_HPP

#include "base_widget.hpp"

namespace singsang
{
class CGoNextWidget : public CBaseWidget
{
public:
    CGoNextWidget(EGuiMode& f_mode, CPlayer& f_player) : CBaseWidget(f_mode, f_player, 270, 190, 40, 40, 20) {}

    void draw(const bool f_updateOnly)
    {
        drawIcon("/media/icon-track-next.png");
    }

    void touch()
    {
        switch (m_mode)
        {
            case EGuiMode::StartupView:
                break;

            case EGuiMode::CategoryView:
                m_player.vibrate();
                m_player.selectNextCategory();
                break;

            case EGuiMode::SongView:
                m_player.vibrate();
                m_player.selectNextSong();
                m_player.playSelectedSong();
                break;
        }
    }

    void update() {}
};

}  // namespace singsang

#endif  // SINGSANG_GO_NEXT_WIDGET_HPP