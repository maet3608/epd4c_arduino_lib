#include "epd4c.h"
#include "imagedata.h"

#define RST_PIN 16
#define DC_PIN 17
#define CS_PIN 5
#define BUSY_PIN 4

#define EPD_WIDTH 168
#define EPD_HEIGHT 400

Epd4c epd(EPD_WIDTH, EPD_HEIGHT, RST_PIN, DC_PIN, CS_PIN, BUSY_PIN);

void setup()
{
  epd.init();
  epd.display(IMAGE_DATA);
  epd.sleep();
}

void loop() {}