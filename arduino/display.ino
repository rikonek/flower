void display(readings object)
{
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
