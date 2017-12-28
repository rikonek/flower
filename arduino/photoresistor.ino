boolean isDay()
{
  // night: 0 < value < 400
  // day: value > 400

  if(analogRead(IN_PHOTORESISTOR) >= 400)
  {
    return true;
  }
  else
  {
    return false;
  }
}

