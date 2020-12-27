#ifndef SINGSANG_BASE_WIDGET_HPP
#define SINGSANG_BASE_WIDGET_HPP

#include <M5Core2.h>
#include <SD.h>

#include "../mode.hpp"
#include "../player.hpp"

namespace singsang
{
class CBaseWidget
{
public:
    CBaseWidget() = delete;

    CBaseWidget(EGuiMode& f_mode, CPlayer& f_player, const int f_positionX, const int f_positionY, const int f_sizeX,
                const int f_sizeY, const int f_touchMargin = 0)
        : m_mode(f_mode)
        , m_player(f_player)
        , m_positionX(f_positionX)
        , m_positionY(f_positionY)
        , m_sizeX(f_sizeX)
        , m_sizeY(f_sizeY)
        , m_touchMargin(f_touchMargin)
    {
    }

    ~CBaseWidget() = default;

    virtual void draw(const bool f_updateOnly) = 0;

    virtual void touch() = 0;

    virtual void update() = 0;

    void init()
    {
        draw(false);
    }

    bool handleTouch(TouchPoint_t f_point)
    //< Returns true if touch event was triggered. A positive touch margin increases the size for touch events.
    {
        const bool isTouchPointInWidget =
            (f_point.x >= (m_positionX - m_touchMargin) && f_point.x < (m_positionX + m_sizeX + m_touchMargin)) &&
            (f_point.y >= (m_positionY - m_touchMargin) && f_point.y < (m_positionY + m_sizeY + m_touchMargin));
        if (!isTouchPointInWidget)
        {
            return false;
        }

        const auto currentTimestamp = millis();
        const bool isDeadTimeOver   = (currentTimestamp > (m_lastTouchTimestamp + m_touchDeadTimeMilliSec));
        if (!isDeadTimeOver)
        {
            return false;
        }

        m_lastTouchTimestamp = currentTimestamp;
        touch();
        return true;
    }

protected:
    void drawIcon(const char* f_iconPath)
    {
        M5.Lcd.drawPngFile(SD, f_iconPath, m_positionX, m_positionY, m_sizeX, m_sizeY);
    }

    EGuiMode& m_mode;
    CPlayer&  m_player;

    unsigned int m_touchDeadTimeMilliSec{500};
    unsigned int m_lastTouchTimestamp{0};
    const int    m_positionX{0};
    const int    m_positionY{0};
    const int    m_sizeX{1};
    const int    m_sizeY{1};
    const int    m_touchMargin{0};
};

}  // namespace singsang

#endif  // SINGSANG_BASE_WIDGET_HPP
