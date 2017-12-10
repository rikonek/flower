uint8_t readButton(int &index)
{
  static uint8_t button_still_pressed=0;
  uint8_t button_pushed=0;

  if(digitalRead(IN_BUTTON_UP)==LOW)
  {
    if(button_still_pressed==0)
    {
      pushButtonUp(index);
    }
    button_still_pressed=1;
    button_pushed=1;
  }
  else if(digitalRead(IN_BUTTON_DOWN)==LOW)
  {
    if(button_still_pressed==0)
    {
      pushButtonDown(index);
    }
    button_still_pressed=1;
    button_pushed=1;
  }
  else
  {
    button_still_pressed=0;
  }
  return button_pushed;
}
void pushButtonUp(int &index)
{
  index--;
  if(index<0) index=MAX_LOGS-1;
}

void pushButtonDown(int &index)
{
  index++;
  if(index>=MAX_LOGS) index=0;
}
