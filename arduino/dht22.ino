float getHumidity()
{
  float humidity=dht.readHumidity();
  if(isnan(humidity)) humidity=-1000;
  return humidity;
}

float getTemperature()
{
  float temperature=dht.readTemperature();
  if(isnan(temperature)) temperature=-1000;
  return temperature;
}

