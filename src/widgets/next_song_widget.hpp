#ifndef SINGSANG_NEXT_SONG_WIDGET_HPP
#define SINGSANG_NEXT_SONG_WIDGET_HPP

#include "base_widget.hpp"

namespace singsang
{
class CNextSongWidget : public CBaseWidget
{
public:
    CNextSongWidget(EGuiMode& f_mode, CPlayer& f_player)
        : CBaseWidget(f_mode, f_player, 270, 180, 40, 40)
    {
    }

    void draw(const bool f_updateOnly)
    {
        drawIcon("/media/icon-track-next.png");
    }

    void touch()
    {
        m_player.vibrate();
        m_player.startNextSong();
    }

    void update() {}
};

}  // namespace singsang

#endif  // SINGSANG_NEXT_SONG_WIDGET_HPP