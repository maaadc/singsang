#include <M5Core2.h>

namespace singsang
{

    class CGui
    {
    public:
        CGui() = default;

        ~CGui() = default;

        void begin()
        {
            // dim LCD, nominal voltage is 2800
            M5.Axp.SetLcdVoltage(2000);

            M5.Lcd.fillScreen(TFT_BLACK);
            M5.Lcd.setTextFont(2);

            M5.Lcd.drawPngFile(SD, "/media/icon-volume-up.png", 10, 40, 40, 40);
            M5.Lcd.drawPngFile(SD, "/media/icon-volume-down.png", 10, 160, 40, 40);

            M5.Lcd.drawPngFile(SD, "/media/icon-battery.png", 270, 40, 40, 40);
            M5.Lcd.drawPngFile(SD, "/media/icon-track-next.png", 270, 160, 40, 40);
        
            drawFileBulletBar(60, 10, 200, 10, 5, 3); // update size and index!

            drawAudioProgressBar(60, 225, 200, 10, 0);

            vibrate();
        }

        void drawAudioProgressBar(int x, int y, int w, int h, uint8_t val)
        {
            const uint16_t col = M5.Lcd.color565(100, 100, 100);
            M5.Lcd.drawRoundRect(x, y, w, h, 2, col);
            M5.Lcd.fillRect(x + 2, y + 2, w - 4, h - 4, TFT_BLACK);
            M5.Lcd.fillRect(x + 2, y + 2, (w - 4) * (((float)val) / 100.0), h - 4, col);
        }

        void drawFileBulletBar(int x, int y, int w, int h, int itemCount, int indexMarked)
        {
            // update background
            M5.Lcd.fillRect(x, y - h, w, 2 * h, TFT_BLACK);

            const uint16_t col = M5.Lcd.color565(100, 100, 100);

            for (int k = 0; k < itemCount; k++)
            {
                const int cx = x + (k + 0.5F) * w / itemCount;
                const int cy = y;
                const int radius = (k == indexMarked) ? h / 2 : h / 5;
                M5.Lcd.fillCircle(cx, cy, radius, col);
            }
        }

        void drawBatteryWidget(int x, int y, int w, int h)
        {
            const bool isCharging = (M5.Axp.GetVinVoltage() > 3.F);
            const float power = M5.Axp.GetBatPower();

            if (isCharging)
            {
                M5.Lcd.drawPngFile(SD, "/media/icon-battery-charging.png", x, y, w, h);
            }
            else
            {
                //const float batteryVoltage = M5.Axp.GetBatVoltage();
                //const float batVoltage = M5.Axp.GetBatVoltage(); // 4.14 V when plugged in

                //const float batPower = 

                M5.Lcd.drawPngFile(SD, "/media/icon-battery-1.png", x, y, w, h);
            }
            
            /*else
            {
                const float power = M5.Axp.GetBatPower();
                if (power > 0.8)
                {
                    M5.Lcd.drawPngFile(SD, "/media/icon-battery-4.png", x, y, w, h);
                }
                else if (power > 0.6)
                {
                    M5.Lcd.drawPngFile(SD, "/media/icon-battery-3.png", x, y, w, h);
                }
                else if (power > 0.4)
                {
                    M5.Lcd.drawPngFile(SD, "/media/icon-battery-2.png", x, y, w, h);
                }
                else if (power > 0.2)
                {
                    M5.Lcd.drawPngFile(SD, "/media/icon-battery-1.png", x, y, w, h);
                }
                else
                {
                    M5.Lcd.drawPngFile(SD, "/media/icon-battery.png", x, y, w, h);
                }
            }
            */
        }

        void vibrate()
        {
            M5.Axp.SetLDOEnable(3, true);
            delay(100);
            M5.Axp.SetLDOEnable(3, false);
        }
    };

} // namespace singsang