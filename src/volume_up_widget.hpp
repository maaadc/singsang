#ifndef SINGSANG_VOLUME_UP_WIDGET_HPP
#define SINGSANG_VOLUME_UP_WIDGET_HPP

#include "base_widget.hpp"

namespace singsang
{
class CVolumeUpWidget : public CBaseWidget
{
public:
    CVolumeUpWidget() : CBaseWidget(10, 40, 40, 40) {}

    void draw(const bool f_updateOnly)
    {
        M5.Lcd.drawPngFile(SD, "/media/icon-volume-up.png", m_positionX,
                           m_positionY, m_sizeX, m_sizeY);
    }
};

}  // namespace singsang

#endif  // SINGSANG_VOLUME_UP_WIDGET_HPP