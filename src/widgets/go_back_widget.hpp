#ifndef SINGSANG_GO_BACK_WIDGET_HPP
#define SINGSANG_GO_BACK_WIDGET_HPP

#include "base_widget.hpp"

namespace singsang
{
class CGoBackWidget : public CBaseWidget
{
public:
    CGoBackWidget(EGuiMode& f_mode, CPlayer& f_player) : CBaseWidget(f_mode, f_player, 270, 10, 40, 40, 20) {}

    void draw(const bool f_updateOnly)
    {
        drawIcon("/media/icon-x.png");
    }

    void touch()
    {
        switch (m_mode)
        {
            case EGuiMode::StartupView:
                break;

            case EGuiMode::CategoryView:
                m_player.switchToMode(m_mode, EGuiMode::StartupView);
                break;

            case EGuiMode::SongView:
                m_player.switchToMode(m_mode, EGuiMode::CategoryView);
                break;
        }
    }

    void update() {}
};

}  // namespace singsang

#endif  // SINGSANG_GO_BACK_WIDGET_HPP