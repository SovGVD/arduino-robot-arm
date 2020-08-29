double cliSetUpperAngle(double value)
{
  HAL_setAngle(UPPER, value);
  return 1;
}

double cliSetLowerAngle(double value)
{
  HAL_setAngle(LOWER, value);
  return 1;
}

double cliSetWristAngle(double value)
{
  HAL_setAngle(WRIST, value);
  return 1;
}
