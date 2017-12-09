int getSoilMoistureAnalog()
{
  return 1024-analogRead(IN_SOIL_MOISTURE);
}

float getSoilMoisture()
{
  uint8_t soil_moisture=map((getSoilMoistureAnalog()),1,800,0,100); // max 870
  if(soil_moisture>100) soil_moisture=100;
  return soil_moisture;
}

soilMoistureStatus getSoilMoistureStatus()
{
  // dry:   0 < value < 300
  // humid: 300 < value < 700
  // water: value > 700

  int soil_moisture=getSoilMoistureAnalog();
  if(soil_moisture>=300)
  {
    return humid;
  }
  else
  {
    return dry;
  }
}
