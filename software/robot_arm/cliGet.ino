double cliGetAngles(double id)
{
  // TODO cliSerial->
  Serial.print(currentArm.upper);
  Serial.print("\t");
  Serial.print(currentArm.lower);
  Serial.print("\t");
  Serial.print(currentArm.wrist);
  Serial.println();

  return 1;
}


double cliGetPosition(double id)
{
  cliSerial->print(gripperPos.x);
  Serial.print("\t");
  cliSerial->print(gripperPos.y);
  cliSerial->println();

  return 1;
}
