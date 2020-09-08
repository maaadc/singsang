#include <M5Core2.h>

void setup()
{
    M5.begin();
    SD.begin();

    M5.Lcd.setBrightness(100);
    M5.Lcd.drawPngFile(SD, "/logo.png", 40, 0, 240, 240, 0, 0, 240. / 512, 127);
}

void loop() {}
