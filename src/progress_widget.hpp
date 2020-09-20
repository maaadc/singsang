#ifndef SINGSANG_PROGRESS_WIDGET_HPP
#define SINGSANG_PROGRESS_WIDGET_HPP

#include "base_widget.hpp"

namespace singsang
{
class CProgressWidget : public CBaseWidget
{
public:
    CProgressWidget() : CBaseWidget(60, 225, 200, 10) {}

    void update(const int f_newProgressPercentage)
    {
        if (f_newProgressPercentage != m_progressPercentage)
        {
            m_progressPercentage = f_newProgressPercentage;
            draw(true);
        }
    }

    void draw(const bool updateOnly)
    {
        const uint16_t color = M5.Lcd.color565(100, 100, 100);
        if (!updateOnly)
        {
            M5.Lcd.drawRoundRect(m_positionX, m_positionY, m_sizeX, m_sizeY, 4,
                                 color);
            M5.Lcd.drawRoundRect(m_positionX + 1, m_positionY + 1, m_sizeX - 2,
                                 m_sizeY - 2, 3, color);
        }
        M5.Lcd.fillRoundRect(m_positionX + 3, m_positionY + 3, m_sizeX - 6,
                             m_sizeY - 6, 2, TFT_BLACK);

        const int barSizeX =
            (m_sizeX - 6) * (((float)m_progressPercentage) / 100.0);
        M5.Lcd.fillRoundRect(m_positionX + 3, m_positionY + 3, barSizeX,
                             m_sizeY - 6, 2, color);
    }

private:
    int m_progressPercentage{0};
};

}  // namespace singsang

#endif  // SINGSANG_PROGRESS_WIDGET_HPP