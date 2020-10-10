#ifndef SINGSANG_NEXT_SONG_WIDGET_HPP
#define SINGSANG_NEXT_SONG_WIDGET_HPP

#include "base_widget.hpp"

namespace singsang
{
class CNextSongWidget : public CBaseWidget
{
public:
    CNextSongWidget(CPlayer& f_player) : CBaseWidget(f_player, 270, 160, 40, 40)
    {
    }

    void draw(const bool f_updateOnly)
    {
        drawIcon("/media/icon-track-next.png");
    }

    void touch()
    {
        m_player.startNextSong();
        m_player.vibrate();
    }

    void update() {}
};

}  // namespace singsang

#endif  // SINGSANG_NEXT_SONG_WIDGET_HPP