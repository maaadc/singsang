#ifndef SINGSANG_VOLUME_DOWN_WIDGET_HPP
#define SINGSANG_VOLUME_DOWN_WIDGET_HPP

#include "base_widget.hpp"

namespace singsang
{
class CVolumeDownWidget : public CBaseWidget
{
public:
    CVolumeDownWidget(EGuiMode& f_mode, CPlayer& f_player) : CBaseWidget(f_mode, f_player, 10, 190, 40, 40, 20) {}

    void draw(const bool f_updateOnly)
    {
        drawIcon("/media/icon-volume-down.png");
    }

    void touch()
    {
        m_player.vibrate();
        m_player.decreaseVolume();
    }

    void update() {}
};

}  // namespace singsang

#endif  // SINGSANG_VOLUME_DOWN_WIDGET_HPP