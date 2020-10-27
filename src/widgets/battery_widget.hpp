#ifndef SINGSANG_BATTERY_WIDGET_HPP
#define SINGSANG_BATTERY_WIDGET_HPP

#include "../helpers.hpp"
#include "base_widget.hpp"

namespace singsang
{
class CBatteryWidget : public CBaseWidget
{
public:
    CBatteryWidget(EGuiMode& f_mode, CPlayer& f_player)
        : CBaseWidget(f_mode, f_player, 270, 100, 40, 40)
    {
    }

    void draw(const bool updateOnly)
    {
        drawIcon(m_currentIconPath.c_str());
    }

    void touch() {}

    void update()
    {
        String newIconPath{m_currentIconPath};

        const bool isCharging = (M5.Axp.GetVinVoltage() > 3.F);
        if (isCharging)
        {
            newIconPath = "/media/icon-battery-charging.png";
        }
        else
        {
            const CFloatRangeMapper battMapper{{3.0F, 4.1F}, {0.F, 1.F}, true};

            const float level = battMapper(M5.Axp.GetBatVoltage());

            if (level < 0.20)
            {
                newIconPath = "/media/icon-battery.png";
            }
            else if (level < 0.40)
            {
                newIconPath = "/media/icon-battery-1.png";
            }
            else if (level < 0.60)
            {
                newIconPath = "/media/icon-battery-2.png";
            }
            else if (level < 0.80)
            {
                newIconPath = "/media/icon-battery-3.png";
            }
            else
            {
                newIconPath = "/media/icon-battery-4.png";
            }
        }

        if (!m_currentIconPath.equals(newIconPath))
        {
            m_currentIconPath = newIconPath;
            draw(true);
        }
    }

private:
    String m_currentIconPath{"/media/icon-battery.png"};
};

}  // namespace singsang

#endif  // SINGSANG_BATTERY_WIDGET_HPP