#ifndef SINGSANG_VOLUME_DISPLAY_WIDGET_HPP
#define SINGSANG_VOLUME_DISPLAY_WIDGET_HPP

#include "base_widget.hpp"

namespace singsang
{
class CVolumeDisplayWidget : public CBaseWidget
{
public:
    CVolumeDisplayWidget(CPlayer& f_player)
        : CBaseWidget(f_player, 10, 80, 40, 80)
    {
    }

    void draw(const bool updateOnly)
    {
        const uint16_t color = M5.Lcd.color565(150, 150, 150);

        for (int volumeIdx = 0; volumeIdx < 4; volumeIdx++)
        {
            const int pointX = m_positionX;
            const int pointY = m_positionY + 55 - 12 * volumeIdx;
            const int sizeX  = 8 * volumeIdx + 12;
            const int sizeY  = 9;

            if (!updateOnly)
            {
                M5.Lcd.drawRoundRect(pointX, pointY, sizeX, sizeY, 4, color);
                M5.Lcd.drawRoundRect(pointX + 1, pointY + 1, sizeX - 2,
                                     sizeY - 2, 3, color);
            }

            const int barIsActive = (m_audioVolume > 4 * volumeIdx);
            const int pickColor   = barIsActive ? color : TFT_BLACK;
            M5.Lcd.fillRoundRect(pointX + 3, pointY + 3, sizeX - 6, sizeY - 6,
                                 2, pickColor);
        }
    }

    void touch() {}

    void update()
    {
        const int newAudioVolume = m_player.getVolume();

        if (newAudioVolume != m_audioVolume)
        {
            m_audioVolume = newAudioVolume;
            draw(true);
        }
    }

private:
    int m_audioVolume;
};

}  // namespace singsang

#endif  // SINGSANG_VOLUME_DISPLAY_WIDGET_HPP