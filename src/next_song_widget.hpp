#ifndef SINGSANG_NEXT_SONG_WIDGET_HPP
#define SINGSANG_NEXT_SONG_WIDGET_HPP

#include "base_widget.hpp"

namespace singsang
{
class CNextSongWidget : public CBaseWidget
{
public:
    CNextSongWidget() : CBaseWidget(270, 160, 40, 40) {}

    void update() {}

    void draw(const bool f_updateOnly)
    {
        M5.Lcd.drawPngFile(SD, "/media/icon-track-next.png", m_positionX,
                           m_positionY, m_sizeX, m_sizeY);
    }
};

}  // namespace singsang

#endif  // SINGSANG_NEXT_SONG_WIDGET_HPP