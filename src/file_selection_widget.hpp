#ifndef SINGSANG_FILE_SELECTION_WIDGET_HPP
#define SINGSANG_FILE_SELECTION_WIDGET_HPP

#include "base_widget.hpp"

namespace singsang
{
class CFileSelectionWidget : public CBaseWidget
{
public:
    CFileSelectionWidget() : CBaseWidget(60, 10, 200, 10) {}

    void update(const int f_newItemCount, const int f_newSelectedIndex)
    {
        if (f_newItemCount != m_itemCount ||
            f_newSelectedIndex != m_selectedIndex)
        {
            m_itemCount     = f_newItemCount;
            m_selectedIndex = f_newSelectedIndex;
            draw(true);
        }
    }

    void draw(const bool updateOnly)
    {
        const int radiusBig   = m_sizeY / 2;
        const int radiusSmall = m_sizeY / 5;

        M5.Lcd.fillRect(m_positionX - radiusBig, m_positionY - m_sizeY,
                        m_sizeX + 2 * radiusBig + 1, 2 * m_sizeY, TFT_BLACK);

        const uint16_t col = M5.Lcd.color565(100, 100, 100);

        for (int k = 0; k < m_itemCount; k++)
        {
            const int cx =
                m_positionX + ((float)k) * m_sizeX / (m_itemCount - 1);
            const int cy     = m_positionY;
            const int radius = (k == m_selectedIndex) ? radiusBig : radiusSmall;
            M5.Lcd.fillCircle(cx, cy, radius, col);
        }
    }

private:
    int m_itemCount{0};
    int m_selectedIndex{-1};
};

}  // namespace singsang

#endif  // SINGSANG_FILE_SELECTION_WIDGET_HPP