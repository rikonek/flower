void display(readings object)
{
  static int old_item_no=0;
  static unsigned long timer_refresh=millis();

  if(old_item_no==object.item_no && (millis()-timer_refresh)<=60000) // 60 seconds
  {
    return;
  }

  timer_refresh=millis();

  old_item_no=object.item_no;

  unsigned long time_ago=readingsTimeToTimeAgo(object.read_time);
  unsigned long time_ago_h=time_ago >> sizeof(uint8_t)*8; // unpacking from long var
  uint8_t time_ago_m=time_ago & 255; // unpacking from long var

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(object.item_no);
  lcd.print(".");
  lcd.setCursor(4,0);
  lcd.print(time_ago_h);
  lcd.print(":");
  if(time_ago_m<10) lcd.print("0");
  lcd.print(time_ago_m);
  lcd.setCursor(10,0);
  lcd.print("T:");
  lcd.print(object.temperature, 1);
  lcd.setCursor(0,1);
  if(object.water_level==-1)
  {
    lcd.print("Err");
  }
  else
  {
    switch(object.water_level)
    {
      case 0: lcd.print("0/4"); break;
      case 25: lcd.print("1/4"); break;
      case 50: lcd.print("2/4"); break;
      case 75: lcd.print("3/4"); break;
      case 100: lcd.print("4/4"); break;
    }
  }
  lcd.setCursor(4,1);
  lcd.print("S:");
  lcd.print(object.soil_moisture);
  lcd.print("%");
  lcd.setCursor(10,1);
  lcd.print("H:");
  lcd.print(object.humidity);
  lcd.print("%");

  #if DEBUG
    Serial.print(object.item_no);
    Serial.print(". H:");
    Serial.print(object.humidity);
    Serial.print("% T:");
    Serial.print(object.temperature, 1);
    Serial.print("*C SM:");
    Serial.print(object.soil_moisture);
    Serial.print("% W:");
    if(object.water_level==-1)
    {
      Serial.print("error");
    }
    else
    {
      Serial.print(object.water_level);
      Serial.print("%");
    }
    Serial.print(" Time:");
    Serial.print(time_ago_h);
    Serial.print(":");
    if(time_ago_m<10) Serial.print("0");
    Serial.print(time_ago_m);
    Serial.println();
  #endif
}

void displayBacklight(boolean on)
{
  static unsigned long timer_backlight=0;

  if(on==true || isDay()==true)
  {
    lcd.backlight();
    if(isDay()==false)
    {
      timer_backlight=millis();
    }
  }

  if(timer_backlight==0 || (millis()-timer_backlight)>=DISPLAY_BACKLIGHT_TIME)
  {
    if(isDay()==false)
    {
      lcd.noBacklight();
    }
    timer_backlight=0;
  }
}

unsigned long readingsTimeToTimeAgo(unsigned long time_ago)
{
  unsigned long minutes=(millis()-time_ago)/1000/60;
  unsigned long h=(minutes-(minutes%60))/60;
  uint8_t m=minutes-(h*60);
  return (h << sizeof(uint8_t)*8) | m; // packing to one long var
}

