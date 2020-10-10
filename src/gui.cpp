#include "gui.hpp"

namespace singsang
{
void CGui::begin()
{
    m_player.begin();

    initializeGui();
}

void CGui::loop()
{
    m_player.loop();

    handleTouchEvents();
    updateGui();
}

template <typename T>
void CGui::addWidget()
{
    m_widgets.emplace_back(std::shared_ptr<T>(new T(m_player)));
}

void CGui::handleTouchEvents()
{
    const auto touchPoint = M5.Touch.getPressPoint();

    const bool isButtonPressed = (touchPoint.x > -1 && touchPoint.y > -1);
    if (!isButtonPressed)
    {
        return;
    }

    for (const auto& widget_p : m_widgets)
    {
        widget_p->handleTouch(touchPoint);
    }
}

void CGui::initializeGui()
{
    M5.Lcd.fillScreen(TFT_BLACK);
    M5.Lcd.setTextFont(2);

    M5.Lcd.drawJpgFile(SD, "/media/logo.jpg", 60, 20, 200, 200);

    addWidget<CBatteryWidget>();
    addWidget<CFileSelectionWidget>();
    addWidget<CNextSongWidget>();
    addWidget<CProgressWidget>();
    addWidget<CVolumeDisplayWidget>();
    addWidget<CVolumeDownWidget>();
    addWidget<CVolumeUpWidget>();
    addWidget<CBatteryWidget>();

    for (const auto& widget_p : m_widgets)
    {
        widget_p->init();
    }
}

void CGui::updateGui()
{
    for (const auto& widget_p : m_widgets)
    {
        widget_p->update();
    }
}

}  // namespace singsang