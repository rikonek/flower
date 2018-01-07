void display(readings object)
{
  static int old_item_no=0;

  if(old_item_no==object.item_no)
  {
    return;
  }

  old_item_no=object.item_no;

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(object.item_no);
  lcd.print(".");
  lcd.setCursor(4,0);
  lcd.print("H:");
  lcd.print(object.humidity);
  lcd.print("% T:");
  lcd.print(object.temperature, 1);
  lcd.setCursor(0,1);
  lcd.print("W:");
  if(object.water_level==-1)
  {
    lcd.print("error");
  }
  else
  {
    lcd.print(object.water_level);
    lcd.print("%");
  }
  lcd.setCursor(9,1);
  lcd.print("SM:");
  lcd.print(object.soil_moisture);
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
