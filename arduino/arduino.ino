#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define IN_DHT 2
#define IN_WATER_LEVEL_0 8
#define IN_WATER_LEVEL_25 9
#define IN_WATER_LEVEL_50 10
#define IN_WATER_LEVEL_75 11
#define IN_WATER_LEVEL_100 12
#define IN_SOIL_MOISTURE A0

#define OUT_BUZZER 13

#define DHTTYPE DHT22
#define MAX_LOGS 36
#define TIME_BETWEEN_READINGS 5000

typedef enum soilMoistureStatus
{
  dry,
  humid
} soilMoistureStatus;

typedef struct readings
{
  uint8_t humidity;
  float temperature;
  uint8_t soil_moisture;
  int8_t water_level;
} readings;

DHT dht(IN_DHT, DHTTYPE);
readings logs[MAX_LOGS]={0};
int log_index=0;
int read_log_index=log_index;
int user_log_index=log_index;

void setup()
{
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

  if(time_readings==0 || (millis()-time_readings)>=TIME_BETWEEN_READINGS)
  {
    readings r={ getHumidity(), getTemperature(), getSoilMoisture(), getWaterLevel() };
    addLog(logs, r);
    time_readings=millis();
  }

  readings current_log=readLog(logs, read_log_index);
  display(current_log);
}