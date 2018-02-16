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
  // sensor in air: 153-159
  // sensor in water: 650-870

  int sm_analog=getSoilMoistureAnalog();
  if(sm_analog<160) sm_analog=160; // fix for map function (set sm_analog as minimum of map)
  uint8_t soil_moisture=map((sm_analog),160,850,0,100);
  if(soil_moisture>100) soil_moisture=100;
  return soil_moisture;
}

soilMoistureStatus getSoilMoistureStatus()
{
  if(getSoilMoisture()>=HUMID_LEVEL)
  {
    return humid;
  }
  else
  {
    return dry;
  }
}
