#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define IN_DHT 2
#define IN_BUTTON_DOWN 4
#define IN_BUTTON_UP 5
#define IN_WATER_LEVEL_0 6
#define IN_WATER_LEVEL_25 7
#define IN_WATER_LEVEL_50 8
#define IN_WATER_LEVEL_75 9
#define IN_WATER_LEVEL_100 10
#define IN_SOIL_MOISTURE A0

#define OUT_SOIL_MOISTURE 11
#define OUT_PUMP 12
#define OUT_BUZZER 13

#define DHTTYPE DHT22
#define MAX_LOGS 36 // int
#define TIME_BETWEEN_READINGS 10000
#define DISPLAY_RETURN_TIME 5000
#define WATERING_DURATION 5000

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

  pinMode(OUT_SOIL_MOISTURE, OUTPUT);
  pinMode(OUT_PUMP, OUTPUT);
  pinMode(OUT_BUZZER, OUTPUT);

  Serial.begin(9600);
  Serial.println("System is running...");
  dht.begin();
}

void loop()
{
  static unsigned long timer_readings=0;
  static unsigned long timer_display_delay=0;
  static unsigned long timer_watering=0;
  static int current_log_index=0;
  static int user_log_index=0;
  static uint8_t display_delay=0;
  static int readings_no;
  uint8_t button_pushed=0;

  if(timer_readings==0 || (millis()-timer_readings)>=TIME_BETWEEN_READINGS)
  {
    soilMoistureOn();
    readings r={ readings_no++, getHumidity(), getTemperature(), getSoilMoisture(), getWaterLevel() };
    current_log_index=addLog(logs, r);
    timer_readings=millis();

    if(getSoilMoistureStatus()==dry)
    {
      pump(WATERING_DURATION, true);
    }
    soilMoistureOff();

    //  alarmOn() || alarmOff()
  }

  pump(WATERING_DURATION, false);

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
      timer_display_delay=millis();
    }
    if(timer_display_delay==0 || (millis()-timer_display_delay)>=DISPLAY_RETURN_TIME)
    {
      display_delay=0;
    }
    button_pushed=0;
  }

  readings current_log=readLog(logs, user_log_index);

  display(current_log);
}
