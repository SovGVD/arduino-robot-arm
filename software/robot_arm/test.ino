void doTests()
{
  if (activeTest == 1) {
    doTest1();
  }
  
}

void doTest1()
{
  double radius = 40;
  // circle around START point

  point newGripper = {
      START_X + radius * dcos(testIteration),
      START_Y + radius * dsin(testIteration)
    };

  HAL_setPosition(newGripper);

  testIteration = testIteration + 1;
  if (testIteration >= 360) {
    testIteration = 0;
  }
}
