#include <ESP8266WiFi.h>
#include <SSD1306.h>
#include <TimeLib.h>
#include <Encoder.h>
#include "DateSelector.h"


// -- OLED Configuration --------------------------------------------------------------------------------------------------

// Refer to https://github.com/squix78/esp8266-oled-ssd1306 for details on Daniel Eichhorn's great library for using an
// SSD1306 display with the ESP8266.  The sketch only uses the basic library to render screens and ignores the advance UI 
// library that provides frames and overlays.
//
 
#define OLED_SDA                                    D1          // pin 14
#define OLED_SDC                                    D2          // pin 12
#define OLED_ADDR                                   0x3C

SSD1306          display(OLED_ADDR, OLED_SDA, OLED_SDC);        // For I2C



// -- TimeLib ------------------------------------------------------------------------------------------------------------

// Refer to https://github.com/PaulStoffregen/Time for details on Paul Stoffregen's time library.  It includes samples on
// synchronising the date and time with various sources including a Real Time Clock, internet NTP time service, GPS time 
// data, and Serial time messages from a computer. This sample code 'hard codes' a date and time for simplicity. 
//



// -- DEBUG Constants -----------------------------------------------------------------------------------------------------
//

#define DEBUG
#define DEBUG_DAY_SELECTOR
#define DEBUG_MONTH_SELECTOR
#define DEBUG_YEAR_SELECTOR


// -- KY-040 Rotary Encoder Values -----------------------------------------------------------------------------------------
//
// Note: The input method (ADC or KY-040) is defined at the top of the sketch.
//

#define KY040_CLK_INPUT                           D5 
#define KY040_DT_INPUT                            D6
#define KY040_SW_INPUT                            D7
#define KY040_MINIMUM_RESOLUTION                  4
#define KY040_LARGE_ROTATION                      16
#define KY040_DEBOUNCE_DELAY                      250

Encoder myEnc(KY040_CLK_INPUT, KY040_DT_INPUT);

long oldPosition  = 0;
boolean isButtonPressed = false;
long lastUpdateMillis = 0;

void handleKey() {
  isButtonPressed = true;  
}


// -- Initialization -----------------------------------------------------------------------------------------------
//
void setup() {

  Serial.begin(115200);

  pinMode(KY040_SW_INPUT, INPUT_PULLUP);
  attachInterrupt(KY040_SW_INPUT, handleKey, RISING);

  display.init();
  display.displayOn();
  
}


// -- Main Loop -----------------------------------------------------------------------------------------------
//

void loop() {

  setTime(12, 0, 0, 2, 9, 2016); 

  time_t t = inputDate(now());

  display.clear();
  display.setColor(WHITE);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0, 30, String(year(t)) + "-" + String(month(t)) + "-" + String(day(t)) + " selected.");
  display.display();
  
  delay(2000);
  
  yield();

}

