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

  switch(water_level)
  {
    case 2:
      analogWrite(OUT_LED_RED, 0);
      if(isDay()==true)
      {
        analogWrite(OUT_LED_GREEN, 255);
      }
      else
      {
        analogWrite(OUT_LED_GREEN, 1);
      }
      break;

    case 1:
      static unsigned long timer_blinking=millis();
      static boolean led_blinking_on=false;

      analogWrite(OUT_LED_RED, 0);
      if((millis()-timer_blinking)>=1000) // 1 seconds
      {
        if(led_blinking_on==false)
        {
          led_blinking_on=true;
          if(isDay()==true)
          {
            analogWrite(OUT_LED_GREEN, 255);
          }
          else
          {
            analogWrite(OUT_LED_GREEN, 1);
          }
        }
        else
        {
          led_blinking_on=false;
          analogWrite(OUT_LED_GREEN, 0);
        }
        timer_blinking=millis();
      }
      break;

    case 0:
    default:
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
}

