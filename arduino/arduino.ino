#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define IN_DHT 2
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
  Serial.begin(9600);
  Serial.println("System is running...");
  dht.begin();
}

void loop()
{
}
