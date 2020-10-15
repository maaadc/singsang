#ifndef SINGSANG_VOLUME_UP_WIDGET_HPP
#define SINGSANG_VOLUME_UP_WIDGET_HPP

#include "base_widget.hpp"

namespace singsang
{
class CVolumeUpWidget : public CBaseWidget
{
public:
    CVolumeUpWidget(CPlayer& f_player) : CBaseWidget(f_player, 10, 40, 40, 40)
    {
    }

    void draw(const bool f_updateOnly)
    {
        drawIcon("/media/icon-volume-up.png");
    }

    void touch()
    {
        m_player.vibrate();
        m_player.increaseVolume();
    }

    void update() {}
};

}  // namespace singsang

#endif  // SINGSANG_VOLUME_UP_WIDGET_HPP