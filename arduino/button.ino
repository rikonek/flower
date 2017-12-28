uint8_t readButton(int &index)
{
  static uint8_t button_still_pressed=0;
  uint8_t button_pushed=0;

  if(digitalRead(IN_BUTTON_MINUS)==LOW)
  {
    if(button_still_pressed==0)
    {
      pushButtonMinus(index);
    }
    button_still_pressed=1;
    button_pushed=1;
  }
  else if(digitalRead(IN_BUTTON_PLUS)==LOW)
  {
    if(button_still_pressed==0)
    {
      pushButtonPlus(index);
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
void pushButtonMinus(int &index)
{
  index--;
  if(index<0) index=MAX_LOGS-1;
}

void pushButtonPlus(int &index)
{
  index++;
  if(index>=MAX_LOGS) index=0;
}
