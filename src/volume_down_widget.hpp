#ifndef SINGSANG_VOLUME_DOWN_WIDGET_HPP
#define SINGSANG_VOLUME_DOWN_WIDGET_HPP

#include "base_widget.hpp"

namespace singsang
{
class CVolumeDownWidget : public CBaseWidget
{
public:
    CVolumeDownWidget() : CBaseWidget(10, 160, 40, 40) {}

    void draw(const bool f_updateOnly)
    {
        M5.Lcd.drawPngFile(SD, "/media/icon-volume-down.png", m_positionX,
                           m_positionY, m_sizeX, m_sizeY);
    }
};

}  // namespace singsang

#endif  // SINGSANG_VOLUME_DOWN_WIDGET_HPP