# Readme

Arduino/ESP32 library for Waveshare 4-color E-paper displays


Should work with the following Waveshare displays, though I tested only with the 3-inch one:
- [3-inch 4-color E-Paper Module 400 × 168](https://amzn.to/3AUpZ7L)
- [2.13-inch 4-color E-Paper Module 250x122](https://amzn.to/417U7a7)
- [2.66-inch 4-color E-Paper Module  360x184](https://amzn.to/4fVKDn1)


Should work with most Arduino, ESP32 and ESP8266 boards. The code is based on the
[Documentation for the Waveshare 3-inch e-Paper Module](https://www.waveshare.com/wiki/3inch_e-Paper_Module_(G)_Manual)

For more details see 
[4-color E-Paper with ESP32]()

## Packaging

Just zip up all the contents as zip file or download this repository as a .zip from GitHub via
`Code -> Download ZIP`

## Installing library

In Arduino IDE menu, go to `Sketch -> Include Libray -> Add .ZIP Library...` 
and then select the zipped library (epd4c_arduino_lib-main.zip).


## Running examples

You can open the example from the Arduino IDE by going to the menu `File -> Examples -> epd4c_drawing -> epd4c_drawing`.

## Example 

```
#include "epd4c.h"

#define RST_PIN 16
#define DC_PIN 17
#define CS_PIN 5
#define BUSY_PIN 4

#define EPD_WIDTH 168
#define EPD_HEIGHT 400

Epd4c epd(EPD_WIDTH, EPD_HEIGHT, RST_PIN, DC_PIN, CS_PIN, BUSY_PIN);

void setup() {
  epd.init();
  epd.setRotation(1);

  epd.fillScreen(WHITE);
  epd.fillCircle(200, 84, 60, RED);
  epd.fillCircle(200, 84, 50, YELLOW);
  epd.fillCircle(200, 84, 40, BLACK);
  epd.fillCircle(200, 84, 30, WHITE);

  epd.setCursor(190, 80);
  epd.setTextColor((BLACK));
  epd.print("Test");
  
  epd.display();
  epd.sleep();
}

void loop() {}

```