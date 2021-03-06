#include "config.h"
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

typedef enum soilMoistureStatus
{
  dry,
  humid
} soilMoistureStatus;

typedef struct readings
{
  int item_no;
  unsigned long read_time;
  uint8_t humidity;
  float temperature;
  uint8_t soil_moisture;
  uint8_t water_level;
} readings;

DHT dht(IN_DHT, DHTTYPE);
readings logs[MAX_LOGS]={0};
LiquidCrystal_I2C lcd(LCD_ADDR, LCD_EN, LCD_RW, LCD_RS, LCD_D4, LCD_D5, LCD_D6, LCD_D7, LCD_BACKLIGHT_PIN, LCD_BACKLIGHT_POL);

void setup()
{
  pinMode(IN_BUTTON_PLUS, INPUT_PULLUP);
  pinMode(IN_BUTTON_MINUS, INPUT_PULLUP);
  pinMode(IN_WATER_LEVEL_EMPTY, INPUT_PULLUP);
  pinMode(IN_WATER_LEVEL_LOW, INPUT_PULLUP);

  pinMode(OUT_SOIL_MOISTURE, OUTPUT);
  pinMode(OUT_PUMP, OUTPUT);
  pinMode(OUT_BUZZER, OUTPUT);
  pinMode(OUT_LED_RED, OUTPUT);
  pinMode(OUT_LED_GREEN, OUTPUT);

  pumpOff();
  noWaterAlarmBuzzerOff();

  #if DEBUG
    Serial.begin(SERIAL_BAUD_RATES);
    Serial.println("Flower project. Please wait...");
  #endif

  dht.begin();

  lcd.begin(16,2); // LCD 16 chars 2 lines
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Flower project");
  lcd.setCursor(1,1);
  lcd.print("Please wait...");
}

void loop()
{
  static unsigned long timer_readings=0;
  static unsigned long timer_display_delay=0;
  static unsigned long timer_watering=0;
  static int current_log_index=0;
  static int user_log_index=0;
  static uint8_t display_delay=0;
  static int readings_no=0;
  uint8_t button_pushed=0;

  if(timer_readings==0 || (millis()-timer_readings)>=TIME_BETWEEN_READINGS)
  {
    soilMoistureOn();
    readings r={ ++readings_no, millis(), getHumidity(), getTemperature(), getSoilMoisture(), getWaterLevel() };
    current_log_index=addLog(logs, r);
    timer_readings=millis();

    if(readings_no>=999) readings_no=0; // I don't have more space in LCD

    if(isDay()==true && getSoilMoistureStatus()==dry && getWaterLevel()>0)
    {
      pump(WATERING_DURATION, true);
    }
    soilMoistureOff();

    if(isDay()==true && getWaterLevel()==0)
    {
      noWaterAlarmBuzzer(NO_WATER_ALARM_DURATION, true);
    }
  }

  waterLevelLed();
  noWaterAlarmBuzzer(NO_WATER_ALARM_DURATION, false);
  pump(WATERING_DURATION, false);
  displayBacklight(false);

  if(display_delay==0)
  {
    user_log_index=current_log_index;
  }

  static boolean logs_array_is_empty=1;
  int tmp_user_log_index;
  if(logs_array_is_empty==1)
  {
    tmp_user_log_index=user_log_index;
  }

  button_pushed=readButton(user_log_index);
  if(button_pushed==1 || display_delay==1)
  {
    displayBacklight(true);

    display_delay=1;

    if(button_pushed==1)
    {
      timer_display_delay=millis();
    }
    if(timer_display_delay==0 || (millis()-timer_display_delay)>=DISPLAY_RETURN_TIME)
    {
      display_delay=0;
    }
    button_pushed=0;
  }

  if(logs_array_is_empty==1 && user_log_index>=readings_no)
  {
    user_log_index=tmp_user_log_index;
  }

  display(readLog(logs, user_log_index));
}
