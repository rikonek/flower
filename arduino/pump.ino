void pump(unsigned int watering_duration, bool run_pump)
{
  static unsigned long timer_watering=0;

  if(run_pump==true)
  {
    pumpOn();
    timer_watering=millis();
  }

  if(timer_watering==0 || (millis()-timer_watering)>=watering_duration)
  {
    pumpOff();
    timer_watering=0;
  }
}

void pumpOn()
{
  digitalWrite(OUT_PUMP, HIGH);
}

void pumpOff()
{
  digitalWrite(OUT_PUMP, LOW);
}
