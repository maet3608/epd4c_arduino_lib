#ifndef EPD4C_H
#define EPD4C_H

#include <SPI.h>
#include <Arduino.h>
#include <Adafruit_GFX.h>

#define BLACK 0x0
#define WHITE 0x1
#define YELLOW 0x2
#define RED 0x3

class Epd4c : public GFXcanvas8
{
public:
  Epd4c(uint16_t width, uint16_t height,
        uint8_t reset_pin, uint8_t dc_pin, uint8_t cs_pin, uint8_t busy_pin);
  ~Epd4c();
  void init();
  void display(unsigned char *Image);
  void display();
  void reset(void);
  void sleep(void);

private:
  uint8_t reset_pin;
  uint8_t dc_pin;
  uint8_t cs_pin;
  uint8_t busy_pin;

  uint8_t *get_image();
  void sendCmd(unsigned char command);
  void sendData(unsigned char data);
  void waitBusyH(void);
  void waitBusyL(void);
  void displayOn(void);
  void spiInit(void);
  void spiTransfer(unsigned char data);
};

#endif /* EPD4C_H */
