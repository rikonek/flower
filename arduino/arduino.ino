#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define IN_DHT 2
#define IN_BUTTON_DOWN 6
#define IN_BUTTON_UP 7
#define IN_WATER_LEVEL_0 8
#define IN_WATER_LEVEL_25 9
#define IN_WATER_LEVEL_50 10
#define IN_WATER_LEVEL_75 11
#define IN_WATER_LEVEL_100 12
#define IN_SOIL_MOISTURE A0

#define OUT_BUZZER 13

#define DHTTYPE DHT22
#define MAX_LOGS 36 // int
#define TIME_BETWEEN_READINGS 5000
#define DISPLAY_RETURN_TIME 5000

typedef enum soilMoistureStatus
{
  dry,
  humid
} soilMoistureStatus;

typedef struct readings
{
  int item_no;
  uint8_t humidity;
  float temperature;
  uint8_t soil_moisture;
  int8_t water_level;
} readings;

DHT dht(IN_DHT, DHTTYPE);
readings logs[MAX_LOGS]={0};

void setup()
{
  pinMode(IN_BUTTON_DOWN, INPUT_PULLUP);
  pinMode(IN_BUTTON_UP, INPUT_PULLUP);
  pinMode(IN_WATER_LEVEL_0, INPUT_PULLUP);
  pinMode(IN_WATER_LEVEL_25, INPUT_PULLUP);
  pinMode(IN_WATER_LEVEL_50, INPUT_PULLUP);
  pinMode(IN_WATER_LEVEL_75, INPUT_PULLUP);
  pinMode(IN_WATER_LEVEL_100, INPUT_PULLUP);

  pinMode(OUT_BUZZER, OUTPUT);

  Serial.begin(9600);
  Serial.println("System is running...");
  dht.begin();
}

void loop()
{
  static unsigned long time_readings=0;
  static unsigned long time_display_delay=0;
  static int current_log_index=0;
  static int user_log_index=0;
  static uint8_t display_delay=0;
  static int readings_no;
  uint8_t button_pushed=0;

  if(time_readings==0 || (millis()-time_readings)>=TIME_BETWEEN_READINGS)
  {
    readings r={ readings_no++, getHumidity(), getTemperature(), getSoilMoisture(), getWaterLevel() };
    current_log_index=addLog(logs, r);
    time_readings=millis();

    //  alarmOn() || alarmOff()
  }

  if(display_delay==0)
  {
    user_log_index=current_log_index;
  }

  button_pushed=readButton(user_log_index);
  if(button_pushed==1 || display_delay==1)
  {
    display_delay=1;

    if(button_pushed==1)
    {
      time_display_delay=millis();
    }
    if(time_display_delay==0 || (millis()-time_display_delay)>=DISPLAY_RETURN_TIME)
    {
      display_delay=0;
    }
    button_pushed=0;
  }

  readings current_log=readLog(logs, user_log_index);

  display(current_log);
}
