#ifndef SINGSANG_VOLUME_DOWN_WIDGET_HPP
#define SINGSANG_VOLUME_DOWN_WIDGET_HPP

#include "base_widget.hpp"

namespace singsang
{
class CVolumeDownWidget : public CBaseWidget
{
public:
    CVolumeDownWidget(CPlayer& f_player)
        : CBaseWidget(f_player, 10, 160, 40, 40)
    {
    }

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