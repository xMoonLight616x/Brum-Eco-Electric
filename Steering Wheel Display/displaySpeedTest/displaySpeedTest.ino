#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Pins used for display 
#define OLED_MOSI   9 // Pin 4 of display
#define OLED_CLK   10 // Pin 3 of display
#define OLED_DC    11 // Pin 6 of display
#define OLED_CS    12 // Pin 7 of display
#define OLED_RESET 13 // Pin 5 of display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

void setup() {
  // Initialze the display:
    if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.display(); // Will display adafruit logo
  // TODO: Change the splash screen to eco racing logo (will have to change the library)
  delay(2000);
  
  display.clearDisplay();

  showSpeed(10.0f);
  delay(1000);
}

void loop(){

}

void showSpeed(float speed) {
  
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 0);
  display.cp437(true);
  
  display.print("OMG IT WORKS");
  display.display();
}
