#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <U8g2lib.h>
#include <RTClib.h>

// Pins used for display 
#define OLED_MOSI   9 // Pin 4 of display
#define OLED_CLK   10 // Pin 3 of display
#define OLED_DC    11 // Pin 6 of display
#define OLED_CS    12 // Pin 7 of display
#define OLED_RESET 13 // Pin 5 of display

// U8G2_SSD1309_128X64_NONAME0_1_4W_SW_SPI u8g2(U8G2_R0, OLED_CLK, OLED_MOSI, OLED_CS, OLED_DC, OLED_RESET);
U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0);

RTC_DS1307 rtc;

// '0', 16x21px
const unsigned char bitmap_big_0 [] PROGMEM = {
  0xf8, 0x0f, 0xf8, 0x0f, 0xf8, 0x0f, 0x07, 0x70, 0x07, 0x70, 0x07, 0x70, 0x07, 0x7e, 0x07, 0x7e, 
  0x07, 0x7e, 0xc7, 0x71, 0xc7, 0x71, 0xc7, 0x71, 0x3f, 0x70, 0x3f, 0x70, 0x3f, 0x70, 0x07, 0x70, 
  0x07, 0x70, 0x07, 0x70, 0xf8, 0x0f, 0xf8, 0x0f, 0xf8, 0x0f
};
// '1', 16x21px
const unsigned char bitmap_big_1 [] PROGMEM = {
  0xc0, 0x01, 0xc0, 0x01, 0xc0, 0x01, 0xf8, 0x01, 0xf8, 0x01, 0xf8, 0x01, 0xc0, 0x01, 0xc0, 0x01, 
  0xc0, 0x01, 0xc0, 0x01, 0xc0, 0x01, 0xc0, 0x01, 0xc0, 0x01, 0xc0, 0x01, 0xc0, 0x01, 0xc0, 0x01, 
  0xc0, 0x01, 0xc0, 0x01, 0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f
};
// '2', 16x21px
const unsigned char bitmap_big_2 [] PROGMEM = {
  0xf8, 0x0f, 0xf8, 0x0f, 0xf8, 0x0f, 0x07, 0x70, 0x07, 0x70, 0x07, 0x70, 0x00, 0x70, 0x00, 0x70, 
  0x00, 0x70, 0xc0, 0x0f, 0xc0, 0x0f, 0xc0, 0x0f, 0x38, 0x00, 0x38, 0x00, 0x38, 0x00, 0x07, 0x00, 
  0x07, 0x00, 0x07, 0x00, 0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f
};
// '3', 16x21px
const unsigned char bitmap_big_3 [] PROGMEM = {
  0xf8, 0x0f, 0xf8, 0x0f, 0xf8, 0x0f, 0x07, 0x70, 0x07, 0x70, 0x07, 0x70, 0x00, 0x70, 0x00, 0x70, 
  0x00, 0x70, 0xc0, 0x0f, 0xc0, 0x0f, 0xc0, 0x0f, 0x00, 0x70, 0x00, 0x70, 0x00, 0x70, 0x07, 0x70, 
  0x07, 0x70, 0x07, 0x70, 0xf8, 0x0f, 0xf8, 0x0f, 0xf8, 0x0f
};
// '4', 16x21px
const unsigned char bitmap_big_4 [] PROGMEM = {
  0x00, 0x7e, 0x00, 0x7e, 0x00, 0x7e, 0xc0, 0x71, 0xc0, 0x71, 0xc0, 0x71, 0x38, 0x70, 0x38, 0x70, 
  0x38, 0x70, 0x07, 0x70, 0x07, 0x70, 0x07, 0x70, 0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0x00, 0x70, 
  0x00, 0x70, 0x00, 0x70, 0x00, 0x70, 0x00, 0x70, 0x00, 0x70
};
// '5', 16x21px
const unsigned char bitmap_big_5 [] PROGMEM = {
  0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0x07, 0x00, 0x07, 0x00, 0x07, 0x00, 0xff, 0x0f, 0xff, 0x0f, 
  0xff, 0x0f, 0x00, 0x70, 0x00, 0x70, 0x00, 0x70, 0x00, 0x70, 0x00, 0x70, 0x00, 0x70, 0x07, 0x70, 
  0x07, 0x70, 0x07, 0x70, 0xf8, 0x0f, 0xf8, 0x0f, 0xf8, 0x0f
};
// '6', 16x21px
const unsigned char bitmap_big_6 [] PROGMEM = {
  0xc0, 0x0f, 0xc0, 0x0f, 0xc0, 0x0f, 0x38, 0x00, 0x38, 0x00, 0x38, 0x00, 0x07, 0x00, 0x07, 0x00, 
  0x07, 0x00, 0xff, 0x0f, 0xff, 0x0f, 0xff, 0x0f, 0x07, 0x70, 0x07, 0x70, 0x07, 0x70, 0x07, 0x70, 
  0x07, 0x70, 0x07, 0x70, 0xf8, 0x0f, 0xf8, 0x0f, 0xf8, 0x0f
};
// '7', 16x21px
const unsigned char bitmap_big_7 [] PROGMEM = {
  0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0x07, 0x70, 0x07, 0x70, 0x07, 0x70, 0x00, 0x70, 0x00, 0x70, 
  0x00, 0x70, 0x00, 0x0e, 0x00, 0x0e, 0x00, 0x0e, 0xc0, 0x01, 0xc0, 0x01, 0xc0, 0x01, 0xc0, 0x01, 
  0xc0, 0x01, 0xc0, 0x01, 0xc0, 0x01, 0xc0, 0x01, 0xc0, 0x01
};
// '8', 16x21px
const unsigned char bitmap_big_8 [] PROGMEM = {
  0xf8, 0x0f, 0xf8, 0x0f, 0xf8, 0x0f, 0x07, 0x70, 0x07, 0x70, 0x07, 0x70, 0x07, 0x70, 0x07, 0x70, 
  0x07, 0x70, 0xf8, 0x0f, 0xf8, 0x0f, 0xf8, 0x0f, 0x07, 0x70, 0x07, 0x70, 0x07, 0x70, 0x07, 0x70, 
  0x07, 0x70, 0x07, 0x70, 0xf8, 0x0f, 0xf8, 0x0f, 0xf8, 0x0f
};
// '9', 16x21px
const unsigned char bitmap_big_9 [] PROGMEM = {
  0xf8, 0x0f, 0xf8, 0x0f, 0xf8, 0x0f, 0x07, 0x70, 0x07, 0x70, 0x07, 0x70, 0x07, 0x70, 0x07, 0x70, 
  0x07, 0x70, 0xf8, 0x7f, 0xf8, 0x7f, 0xf8, 0x7f, 0x00, 0x70, 0x00, 0x70, 0x00, 0x70, 0x00, 0x0e, 
  0x00, 0x0e, 0x00, 0x0e, 0xf8, 0x01, 0xf8, 0x01, 0xf8, 0x01
};

// 'small_0', 6x7px
const unsigned char bitmap_small_0 [] PROGMEM = {
  0x0e, 0x11, 0x19, 0x15, 0x13, 0x11, 0x0e
};
// 'small_1', 6x7px
const unsigned char bitmap_small_1 [] PROGMEM = {
  0x04, 0x06, 0x04, 0x04, 0x04, 0x04, 0x1f
};
// 'small_2', 6x7px
const unsigned char bitmap_small_2 [] PROGMEM = {
  0x0e, 0x11, 0x10, 0x0c, 0x02, 0x01, 0x1f
};
// 'small_3', 6x7px
const unsigned char bitmap_small_3 [] PROGMEM = {
  0x0e, 0x11, 0x10, 0x0c, 0x10, 0x11, 0x0e
};
// 'small_4', 6x7px
const unsigned char bitmap_small_4 [] PROGMEM = {
  0x18, 0x14, 0x12, 0x11, 0x1f, 0x10, 0x10
};
// 'small_5', 6x7px
const unsigned char bitmap_small_5 [] PROGMEM = {
  0x1f, 0x01, 0x0f, 0x10, 0x10, 0x11, 0x0e
};
// 'small_6', 6x7px
const unsigned char bitmap_small_6 [] PROGMEM = {
  0x0c, 0x02, 0x01, 0x0f, 0x11, 0x11, 0x0e
};
// 'small_7', 6x7px
const unsigned char bitmap_small_7 [] PROGMEM = {
  0x1f, 0x11, 0x10, 0x08, 0x04, 0x04, 0x04
};
// 'small_8', 6x7px
const unsigned char bitmap_small_8 [] PROGMEM = {
  0x0e, 0x11, 0x11, 0x0e, 0x11, 0x11, 0x0e
};
// 'small_9', 6x7px
const unsigned char bitmap_small_9 [] PROGMEM = {
  0x0e, 0x11, 0x11, 0x1e, 0x10, 0x08, 0x06
};

// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 320)
const int bitmap_allArray_LEN = 10;
const unsigned char* bitmap_allArray[10] = {
  bitmap_small_0,
  bitmap_small_1,
  bitmap_small_2,
  bitmap_small_3,
  bitmap_small_4,
  bitmap_small_5,
  bitmap_small_6,
  bitmap_small_7,
  bitmap_small_8,
  bitmap_small_9
};


// 'mph', 32x12px
const unsigned char bitmap_mph [] PROGMEM = {
  0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x60, 0x00, 0x38, 0xb1, 0x63, 0x07, 
  0xf8, 0xf7, 0xef, 0x1f, 0xd8, 0x76, 0xec, 0x18, 0xd8, 0x36, 0x6c, 0x18, 0xd8, 0xf6, 0x6f, 0x18, 
  0x18, 0xf6, 0x63, 0x18, 0x18, 0x36, 0x60, 0x18, 0x18, 0x36, 0x60, 0x18, 0x00, 0x30, 0x00, 0x00
};

// 'time_colon', 4x18px
const unsigned char bitmap_colon [] PROGMEM = {
  0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x07, 
  0x07, 0x07
};

// 'percentage', 6x7px
const unsigned char bitmap_percentage [] PROGMEM = {
  0x11, 0x09, 0x08, 0x04, 0x02, 0x12, 0x11
};

// (Total bytes used to store images in PROGMEM = 640)
const int big_numbers_LEN = 10;
const unsigned char* big_numbers[10] = {
  bitmap_big_0,
  bitmap_big_1,
  bitmap_big_2,
  bitmap_big_3,
  bitmap_big_4,
  bitmap_big_5,
  bitmap_big_6,
  bitmap_big_7,
  bitmap_big_8,
  bitmap_big_9
};

// (Total bytes used to store images in PROGMEM = 320)
const int small_numbers_LEN = 10;
const unsigned char* small_numbers[10] = {
  bitmap_small_0,
  bitmap_small_1,
  bitmap_small_2,
  bitmap_small_3,
  bitmap_small_4,
  bitmap_small_5,
  bitmap_small_6,
  bitmap_small_7,
  bitmap_small_8,
  bitmap_small_9
};

int speed;
DateTime now;
int battery_percentage;

void setup() {
  u8g2.begin();
  u8g2.setDrawColor(1);
  u8g2.setBitmapMode(1);

  rtc.begin();

  pinMode(A0, INPUT);
}

void loop() {

  now = rtc.now();
  speed = map(analogRead(A0), 0, 1023, 0, 300) / 10;
  battery_percentage = 69;

  u8g2.firstPage();
  do {
    // Update dynamic components of the screen
    updateSpeed(speed);
    updateTime(now);
    updateBattery(battery_percentage);

    // Draw the "permanent" objects on screen
    u8g2.drawXBMP(48,53,32,12,bitmap_mph);
    u8g2.drawXBMP(62,5,4,18,bitmap_colon);
    u8g2.drawXBMP(116,35,6,7,bitmap_percentage);
  } while (u8g2.nextPage());
}

void updateSpeed(int s) {
  char speed_string[4];
  itoa(s, speed_string, 10);
  int speed_string_length = strlen(speed_string);

  for (int i=0; i < speed_string_length; i++) {
    u8g2.drawXBMP((64 - speed_string_length*8) + 18*i, 30, 16, 21, big_numbers[speed_string[i] - 48]);
  }
}

void updateTime(DateTime t) {
  char hour_string[2];
  char minute_string[2];

  // itoa(t.hour(), hour_string, 10);
  sprintf(hour_string, "%02d", t.hour());
  // itoa(t.minute(), minute_string, 10);
  sprintf(minute_string, "%02d", t.minute());

  for (int i=0; i <= 1; i++) {
    u8g2.drawXBMP( 26 + 18*i, 3, 16, 21, big_numbers[hour_string[i] - 48]);
    u8g2.drawXBMP( 68 + 18*i, 3, 16, 21, big_numbers[minute_string[i] - 48]);
  }
}

void updateBattery(int b) {
  char bat_string[3];
  itoa(b, bat_string, 10);
  int bat_str_len = strlen(bat_string);


  // u8g2.drawXBMP(98,35,6,7,small_numbers[bat_string[0] - 48]);
  // u8g2.drawXBMP(104,35,6,7,small_numbers[bat_string[1] - 48]);
  // u8g2.drawXBMP(110,35,6,7,small_numbers[bat_string[2] - 48]);
  
  for (int i=0; i<bat_str_len; i++) {
    u8g2.drawXBMP((116 - bat_str_len*6) + 6*i, 35, 6, 7, small_numbers[bat_string[i] - 48]);
  }
}
