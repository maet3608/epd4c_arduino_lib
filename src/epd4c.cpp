#include <stdlib.h>
#include "epd4c.h"


Epd4c::Epd4c(uint16_t width, uint16_t height, 
         uint8_t reset_pin, uint8_t dc_pin, uint8_t cs_pin, uint8_t busy_pin)
    : GFXcanvas8(width, height) {
    this->reset_pin = reset_pin;
    this->dc_pin = dc_pin;
    this->cs_pin = cs_pin;
    this->busy_pin = busy_pin;
  }

Epd4c::~Epd4c(){};

void Epd4c::init() {
  spiInit();
  reset();
  sendCmd(0x66);
  sendData(0x49);
  sendData(0x55);
  sendData(0x13);
  sendData(0x5D);
  sendData(0x05);
  sendData(0x10);

  sendCmd(0xB0);
  sendData(0x00);  //1 boost

  sendCmd(0x01);
  sendData(0x0F);
  sendData(0x00);

  sendCmd(0x00);
  sendData(0x4F);
  sendData(0x6B);

  sendCmd(0x06);
  sendData(0xD7);
  sendData(0xDE);
  sendData(0x12);

  sendCmd(0x61);
  sendData(0x00);
  sendData(0xA8);
  sendData(0x01);
  sendData(0x90);

  sendCmd(0x50);
  sendData(0x37);

  sendCmd(0x60);
  sendData(0x0C);
  sendData(0x05);

  sendCmd(0xE3);
  sendData(0xFF);

  sendCmd(0x84);
  sendData(0x00);
}

void Epd4c::sendCmd(unsigned char command) {
  digitalWrite(dc_pin, LOW);
  spiTransfer(command);
}

void Epd4c::sendData(unsigned char data) {
  digitalWrite(dc_pin, HIGH);
  spiTransfer(data);
}

void Epd4c::waitBusyH(void) {
  while (digitalRead(busy_pin) == LOW) {  //LOW: busy, HIGH: idle
    delay(5);
  }
}

void Epd4c::waitBusyL(void) {
  while (digitalRead(busy_pin) == HIGH) {  //LOW: idle, HIGH: busy
    delay(5);
  }
}

void Epd4c::reset(void) {
  digitalWrite(reset_pin, HIGH);
  delay(20);
  digitalWrite(reset_pin, LOW);  //module reset
  delay(2);
  digitalWrite(reset_pin, HIGH);
  delay(20);
}

void Epd4c::displayOn(void) {
  sendCmd(0x12);  // DISPLAY_REFRESH
  sendData(0x01);
  waitBusyH();

  sendCmd(0x02);  // POWER_OFF
  sendData(0X00);
  waitBusyH();
}

void Epd4c::display(unsigned char* Image) {
  unsigned int w = (width() % 4 == 0) ? (width() / 4) : (width() / 4 + 1);
  unsigned int h = height();

  sendCmd(0x04);
  waitBusyH();
  sendCmd(0x10);
  for (unsigned int j = 0; j < h; j++) {
    for (unsigned int i = 0; i < w; i++) {
      sendData(Image[i + j * w]);
    }
  }
  displayOn();
}

uint8_t* Epd4c::get_image() {
  uint8_t* buf = getBuffer();
  int n = width() * height();
  int ci = 0;
  for (int i = 0; i < n; i += 4) {
    uint8_t com = buf[i];
    com = (com << 2) | buf[i + 1];
    com = (com << 2) | buf[i + 2];
    com = (com << 2) | buf[i + 3];
    buf[ci++] = com;
  }
  return buf;
}

void Epd4c::display() {
  uint8_t* buf = get_image();
  display(buf);
}

void Epd4c::sleep(void) {
  sendCmd(0x02);  // POWER_OFF
  sendData(0X00);
  sendCmd(0x07);  // DEEP_sleep
  sendData(0XA5);
}

void Epd4c::spiTransfer(unsigned char data) {
  digitalWrite(cs_pin, LOW);
  SPI.transfer(data);
  digitalWrite(cs_pin, HIGH);
}

void Epd4c::spiInit(void) {
  pinMode(cs_pin, OUTPUT);
  pinMode(reset_pin, OUTPUT);
  pinMode(dc_pin, OUTPUT);
  pinMode(busy_pin, INPUT);

  SPI.begin();
  SPI.endTransaction();
  SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0));
}
