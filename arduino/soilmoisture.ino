void soilMoistureOn()
{
  digitalWrite(OUT_SOIL_MOISTURE, HIGH);
  delay(200);
}

void soilMoistureOff()
{
  digitalWrite(OUT_SOIL_MOISTURE, LOW);
  delay(200);
}

int getSoilMoistureAnalog()
{
  return 1024-analogRead(IN_SOIL_MOISTURE);
}

uint8_t getSoilMoisture()
{
  // sensor in air: 153
  // sensor in water: 650-870

  uint8_t soil_moisture=map((getSoilMoistureAnalog()),150,850,0,100);
  if(soil_moisture>100) soil_moisture=100;
  return soil_moisture;
}

soilMoistureStatus getSoilMoistureStatus()
{
  if(getSoilMoisture()>40)
  {
    return humid;
  }
  else
  {
    return dry;
  }
}
