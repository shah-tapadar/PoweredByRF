/**
 * @Author Tapadar S
 * @Date May 15, 2018
 * @Setup Aurdino Mega, 3.3 RF Receiver, Adafruit Display, BLE, LED
 * @Version Aurdino 1.8.4
 * @Purpose The RF receiver receives a signal with message from the RF transmitter and displays it in Adafruit LCD and also transmits over BLE
 * @Deploy This code to be deployed in Aurdino Mega that acts as receiver.
 * 
 */
#include <RadioHead.h>
#include <radio_config_Si4460.h>
#include <RHCRC.h>
#include <RHDatagram.h>
#include <RHGenericDriver.h>
#include <RHGenericSPI.h>
#include <RHHardwareSPI.h>
#include <RHMesh.h>
#include <RHNRFSPIDriver.h>
#include <RHReliableDatagram.h>
#include <RHRouter.h>
#include <RHSoftwareSPI.h>
#include <RHSPIDriver.h>
#include <RHTcpProtocol.h>
#include <RH_ASK.h>
#include <RH_NRF24.h>
#include <RH_NRF905.h>
#include <RH_RF22.h>
#include <RH_RF24.h>
#include <RH_RF69.h>
#include <RH_RF95.h>
#include <RH_Serial.h>
#include <RH_TCP.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define LOG16_GLCD_HEIGHT 16
#define LOG16_GLCD_WIDTH 16

static const unsigned char PROGMEM log16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000
};

RH_ASK driver;
int ledLevel = 0;

void setup() {

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  //ADCSRA &= ~(bit (ADPS0) | bit (ADPS1) | bit (ADPS2)); // clear prescaler bits

  display.display();
  delay(2000);

  //clear the buffer
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("RF Field Detector");
  display.display();
  delay(2000);
  display.clearDisplay();

  Serial.begin(9600); // Debugging only
  pinMode(9, OUTPUT);
  //pinMode(22, INPUT);

  if (!driver.init()){
     Serial.println("init failed");
  }
}

void loop() {
  
  uint8_t buf[12];
  uint8_t buflen = sizeof(buf);
  char* message ;
  String detect;

  if (driver.recv(buf, &buflen)) // Non-blocking
  {
    // Message with a good checksum received, dump it.
    //Serial.print("Message: ");
    //Serial.println((char*)buf);
    detect = "RF Detected";
    message = (char*)buf;
    ledLevel = map(1024,0,1024,0,255);  
  }else{
    detect = "No RF Signal";
    message = "No_Message";
    ledLevel = 0;
  }

  Serial.print(message);
  //Serial.println(message);

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println(detect);
  display.println(message);
  display.display();
  analogWrite(9, ledLevel);
  display.clearDisplay();
  delay(1000);

}
