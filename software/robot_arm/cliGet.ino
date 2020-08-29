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
