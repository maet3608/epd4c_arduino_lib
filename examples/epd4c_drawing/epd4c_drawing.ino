#include "epd4c.h"

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