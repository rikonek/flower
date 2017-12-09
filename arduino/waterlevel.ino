int8_t getWaterLevel()
{
  int8_t water_level=-1;
  if(digitalRead(IN_WATER_LEVEL_100)==LOW)
  {
    water_level=100;
  }
  else if(digitalRead(IN_WATER_LEVEL_75)==LOW)
  {
    water_level=75;
  }
  else if(digitalRead(IN_WATER_LEVEL_50)==LOW)
  {
    water_level=50;
  }
  else if(digitalRead(IN_WATER_LEVEL_25)==LOW)
  {
    water_level=25;
  }
  else if(digitalRead(IN_WATER_LEVEL_0)==LOW)
  {
    water_level=0;
  }
  return water_level;
}
