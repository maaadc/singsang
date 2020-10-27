#ifndef SINGSANG_GO_BACK_WIDGET_HPP
#define SINGSANG_GO_BACK_WIDGET_HPP

#include "base_widget.hpp"

namespace singsang
{
class CGoBackWidget : public CBaseWidget
{
public:
    CGoBackWidget(EGuiMode& f_mode, CPlayer& f_player)
        : CBaseWidget(f_mode, f_player, 270, 20, 40, 40)
    {
    }

    void draw(const bool f_updateOnly)
    {
        drawIcon("/media/icon-x.png");
    }

    void touch()
    {
        m_player.vibrate();

        switch (m_mode)
        {
            case EGuiMode::StartupView:
                break;

            case EGuiMode::CategoryView:
                m_mode = EGuiMode::StartupView;
                break;

            case EGuiMode::SongView:
                m_mode = EGuiMode::CategoryView;
                break;
        }
    }

    void update() {}
};

}  // namespace singsang

#endif  // SINGSANG_GO_BACK_WIDGET_HPP