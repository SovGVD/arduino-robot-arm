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

double cliSetPositionX(double x)
{
  HAL_setPositionByAxis(POINT_X, x);
  return 1;
}

double cliSetPositionY(double y)
{
  HAL_setPositionByAxis(POINT_Y, y);
  return 1;
}

double cliSetTest(double testId)
{
  activeTest = testId;
  testIteration = 0;
  
  return testId;
}
