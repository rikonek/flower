boolean isDay()
{
  // night: 0 < value < 500
  // day: value > 500

  if(analogRead(IN_PHOTORESISTOR) >= 500)
  {
    return true;
  }
  else
  {
    return false;
  }
}

