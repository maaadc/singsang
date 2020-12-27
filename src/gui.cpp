#include "gui.hpp"

#include "widgets/battery_widget.hpp"
#include "widgets/file_selection_widget.hpp"
#include "widgets/go_back_widget.hpp"
#include "widgets/go_next_widget.hpp"
#include "widgets/go_select_widget.hpp"
#include "widgets/progress_widget.hpp"
#include "widgets/volume_display_widget.hpp"
#include "widgets/volume_down_widget.hpp"
#include "widgets/volume_up_widget.hpp"

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
    m_widgets.emplace_back(std::shared_ptr<T>(new T(m_mode, m_player)));
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

    m_player.updateCategoryIcon(EGuiMode::StartupView);

    addWidget<CBatteryWidget>();
    addWidget<CFileSelectionWidget>();
    addWidget<CGoNextWidget>();
    addWidget<CGoBackWidget>();
    addWidget<CGoSelectWidget>();
    addWidget<CProgressWidget>();
    addWidget<CVolumeDisplayWidget>();
    addWidget<CVolumeDownWidget>();
    addWidget<CVolumeUpWidget>();

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