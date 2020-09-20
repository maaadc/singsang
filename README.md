# singsang

Music player for an [M5Stack Core2](https://m5stack.com/collections/all/products/m5stack-core2-esp32-iot-development-kit), which is based on an ESP32 Microcontroller.
The simple GUI is specifically designed for children, who are able to choose a song based on the displayed album art.

![M5Stack Core2 running singsang](/media/singsang.jpg?raw=true)


## Features
- [x] Mp3 playback from SD card with a simple GUI
- [x] Add battery status indicator
- [x] Timeout for touchscreen clicks to prevent multiple activations
- [ ] Turn itself off, if it does not play for 5 minutes


## Considerations
The player expects Mp3 files in the folder `/music` on the SD card.
Album art is only displayed properly if it is embedded in the Mp3 file as Jpeg of size 400 x 400.
Items in the media folder need to be placed in `/media` on the SD card.


## Credit
This project uses the [M5Core2](https://github.com/m5stack/M5Core2) library to access peripherals and [ESP32-audioI2S](https://github.com/schreibfaul1/ESP32-audioI2S) for high quality audio replay.
The beautiful [Giraffe](https://publicdomainvectors.org/en/free-clipart/Cartoon-giraffe-image/49785.html) logo is taken from publicdomainvectors.org. The buttons are based on the [Tabler](https://github.com/tabler/tabler-icons) icon set. 


