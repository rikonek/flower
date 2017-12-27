void display(readings object)
{
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print(object.item_no);
  lcd.print(".");
  lcd.setCursor(3,0);
  lcd.print("H:");
  lcd.print(object.humidity);
  lcd.print("%  T:");
  lcd.print(object.temperature, 1);
  lcd.setCursor(2,1);
  lcd.print("SM:");
  lcd.print(object.soil_moisture);
  lcd.print("% WL:");
  lcd.print(object.water_level);
  Serial.print(object.item_no);
  Serial.print(". ");
  Serial.print(object.humidity);
  Serial.print("% ");
  Serial.print(object.temperature, 1);
  Serial.print("*C ");
  Serial.print(object.soil_moisture);
  Serial.print("% ");
  Serial.print(object.water_level);
  Serial.println("");
}
