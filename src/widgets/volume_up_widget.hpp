#ifndef SINGSANG_VOLUME_UP_WIDGET_HPP
#define SINGSANG_VOLUME_UP_WIDGET_HPP

#include "base_widget.hpp"

namespace singsang
{
class CVolumeUpWidget : public CBaseWidget
{
public:
    CVolumeUpWidget(EGuiMode& f_mode, CPlayer& f_player) : CBaseWidget(f_mode, f_player, 10, 10, 40, 40, 20) {}

    void draw(const bool f_updateOnly)
    {
        drawIcon("/media/icon-volume-up.png");
    }

    void touch()
    {
        m_player.increaseVolume();
        m_player.vibrate();
    }

    void update() {}
};

}  // namespace singsang

#endif  // SINGSANG_VOLUME_UP_WIDGET_HPP