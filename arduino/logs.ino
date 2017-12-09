void addLog(readings *logs, readings &object)
{
  read_log_index=log_index;
  logs[log_index]=object;
  log_index++;
  if(log_index>=MAX_LOGS) log_index=0;
}

readings readLog(readings *logs, int index)
{
  return logs[index];
}