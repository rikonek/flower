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

#define DHTTYPE DHT22

typedef enum soilMoistureStatus
{
  dry,
  humid
} soilMoistureStatus;

DHT dht(IN_DHT, DHTTYPE);

void setup()
{
  pinMode(IN_WATER_LEVEL_0, INPUT_PULLUP);
  pinMode(IN_WATER_LEVEL_25, INPUT_PULLUP);
  pinMode(IN_WATER_LEVEL_50, INPUT_PULLUP);
  pinMode(IN_WATER_LEVEL_75, INPUT_PULLUP);
  pinMode(IN_WATER_LEVEL_100, INPUT_PULLUP);

  Serial.begin(9600);
  Serial.println("System is running...");
  dht.begin();
}

void loop()
{
}
