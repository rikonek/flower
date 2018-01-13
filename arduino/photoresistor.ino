boolean isDay()
{
  // night: 0 < value < 200
  // day: value > 200

  if(analogRead(IN_PHOTORESISTOR) >= 200)
  {
    return true;
  }
  else
  {
    return false;
  }
}

