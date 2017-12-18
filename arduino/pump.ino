uint8_t pump(uint8_t is_dry, unsigned int watering_duration)
{
  static unsigned long timer_watering=0;
  uint8_t status=0;

  if(is_dry==1)
  {
    pumpOn();
    status=1;
  }

  if(timer_watering==0 || (millis()-timer_watering)>=watering_duration)
  {
    pumpOff();
    status=0;
    timer_watering=millis();
  }
  return status;
}

void pumpOn()
{
  digitalWrite(OUT_PUMP, HIGH);
}

void pumpOff()
{
  digitalWrite(OUT_PUMP, LOW);
}
