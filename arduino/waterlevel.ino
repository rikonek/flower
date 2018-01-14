uint8_t getWaterLevel()
{
  uint8_t water_level=2;
  if(digitalRead(IN_WATER_LEVEL_EMPTY)==LOW)
  {
    water_level=0;
  }
  else if(digitalRead(IN_WATER_LEVEL_LOW)==LOW)
  {
    water_level=1;
  }
  return water_level;
}

void noWaterAlarmBuzzer(unsigned int alarm_duration, bool run_alarm)
{
  static unsigned long timer_alarm=0;

  if(run_alarm==true)
  {
    noWaterAlarmBuzzerOn();
    timer_alarm=millis();
  }

  if(timer_alarm==0 || (millis()-timer_alarm)>=alarm_duration)
  {
    noWaterAlarmBuzzerOff();
    timer_alarm=0;
  }
}

void noWaterAlarmBuzzerOn()
{
  digitalWrite(OUT_BUZZER, HIGH);
}

void noWaterAlarmBuzzerOff()
{
  digitalWrite(OUT_BUZZER, LOW);
}

void waterLevelLed()
{
  uint8_t water_level=getWaterLevel();

  if(water_level==0)
  {
    analogWrite(OUT_LED_GREEN, 0);
    if(isDay()==true)
    {
      analogWrite(OUT_LED_RED, 255);
    }
    else
    {
      analogWrite(OUT_LED_RED, 1);
    }
  }
  else
  {
    analogWrite(OUT_LED_RED, 0);
    if(isDay()==true)
    {
      analogWrite(OUT_LED_GREEN, 255);
    }
    else
    {
      analogWrite(OUT_LED_GREEN, 1);
    }
  }
}

