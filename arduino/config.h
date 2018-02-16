#ifndef CONFIG_H
#define CONFIG_H

#define IN_SOIL_MOISTURE A0
#define IN_PHOTORESISTOR A1

#define OUT_SDA A4
#define OUT_SCL A5

#define IN_DHT 3
#define IN_WATER_LEVEL_EMPTY 7
#define IN_WATER_LEVEL_LOW 8
#define IN_BUTTON_PLUS 16 // 16 = A2
#define IN_BUTTON_MINUS 17 // 17 = A3

#define OUT_LED_RED 9
#define OUT_LED_GREEN 10
#define OUT_SOIL_MOISTURE 11
#define OUT_PUMP 12
#define OUT_BUZZER 13

#define MAX_LOGS 48 // int
#define TIME_BETWEEN_READINGS 600000 // ms
#define DISPLAY_RETURN_TIME 5000 // ms
#define DISPLAY_BACKLIGHT_TIME 5000 // ms
#define WATERING_DURATION 3500 // ms
#define NO_WATER_ALARM_DURATION 5000 // ms
#define HUMID_LEVEL 30 // percent

#define DEBUG 0

#if DEBUG
  #define TIME_BETWEEN_READINGS 5000 // ms
#endif

#define DHTTYPE DHT22
#define LCD_ADDR 0x27 // LCD I2C address
#define LCD_EN 2
#define LCD_RW 1
#define LCD_RS 0
#define LCD_D4 4
#define LCD_D5 5
#define LCD_D6 6
#define LCD_D7 7
#define LCD_BACKLIGHT_PIN 3
#define LCD_BACKLIGHT_POL POSITIVE
#define SERIAL_BAUD_RATES 9600

#endif
