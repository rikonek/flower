int addLog(readings *logs, readings &object)
{
  static int index=0;
  int read_index=index;

  logs[index]=object;
  index++;
  if(index>=MAX_LOGS) index=0;
  return read_index;
}

readings readLog(readings *logs, int index)
{
  return logs[index];
}
