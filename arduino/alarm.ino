void alarm(unsigned int alarm_duration, bool run_alarm)
{
  static unsigned long timer_alarm=0;

  if(run_alarm==true)
  {
    alarmOn();
    timer_alarm=millis();
  }

  if(timer_alarm==0 || (millis()-timer_alarm)>=alarm_duration)
  {
    alarmOff();
    timer_alarm=0;
  }
}

void alarmOn()
{
  digitalWrite(OUT_BUZZER, HIGH);
}

void alarmOff()
{
  digitalWrite(OUT_BUZZER, LOW);
}
