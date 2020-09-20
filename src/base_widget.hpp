#ifndef SINGSANG_BASE_WIDGET_HPP
#define SINGSANG_BASE_WIDGET_HPP

#include <M5Core2.h>
#include <SD.h>

namespace singsang
{
class CBaseWidget
{
public:
    CBaseWidget() {}
    CBaseWidget(const int f_positionX, const int f_positionY, const int f_sizeX,
                const int f_sizeY)
        : m_positionX(f_positionX)
        , m_positionY(f_positionY)
        , m_sizeX(f_sizeX)
        , m_sizeY(f_sizeY)
    {
    }

    ~CBaseWidget() = default;

    bool isTouched(TouchPoint_t f_point)
    {
        const bool isTouchPointInWidget =
            (f_point.x >= m_positionX && f_point.x < (m_positionX + m_sizeX)) &&
            (f_point.y >= m_positionY && f_point.y < (m_positionY + m_sizeY));

        return isTouchPointInWidget;
    }

    virtual void draw(const bool f_updateOnly) = 0;

protected:
    const int m_positionX{0};
    const int m_positionY{0};
    const int m_sizeX{1};
    const int m_sizeY{1};
};

}  // namespace singsang

#endif  // SINGSANG_BASE_WIDGET_HPP
