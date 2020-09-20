# singsang

Music player using an [M5Stack Core2](https://m5stack.com/collections/all/products/m5stack-core2-esp32-iot-development-kit), which is based on an ESP32 Microcontroller.


## Features
- [x] Mp3 playback from SD card with a simple GUI
- [ ] Add battery status indicator
- [ ] Timeout for touchscreen clicks to prevent multiple activations
- [ ] Turn itself off, if it does not play for 5 minutes


## Considerations
The player expects Mp3 files in the folder `/music` on the SD card. Album art is only displayed properly if it is embedded in the Mp3 file as Jpeg of size 400 x 400.

Icons from: https://github.com/tabler/tabler-icons


