
arm previousArm = {UPPER_ARM_ANGLE, LOWER_ARM_ANGLE, WRIST_ANGLE, GRIPPER_ANGLE};
arm currentArm  = {UPPER_ARM_ANGLE, LOWER_ARM_ANGLE, WRIST_ANGLE, GRIPPER_ANGLE};
arm newArm      = {UPPER_ARM_ANGLE, LOWER_ARM_ANGLE, WRIST_ANGLE, GRIPPER_ANGLE};

double lever_a_sq = LEVER_A*LEVER_A;
double lever_b_sq = LEVER_B*LEVER_B;
double lever_c_sq = LEVER_C*LEVER_C;
double lever_d_sq = LEVER_D*LEVER_D;

double lever_lower_angle_middle = HAL_getAngleFromJointAngle(SERVO_MIDDLE_ANGLE);
double lever_wrist_angle_middle = HAL_getAngleFromJointAngle(SERVO_MIDDLE_ANGLE);

void HAL_setAngle(uint8_t angleId, double value)
{
  previousArm = currentArm;

  switch(angleId) {
    case UPPER:
      currentArm.upper = value;
      break;
    case LOWER:
      currentArm.lower = value;
      break;
    case WRIST:
      currentArm.wrist = value;
      break;
  }
  
  newArm = currentArm;
  HAL_transition();  
}

void HAL_setAngles(arm angles)
{
  previousArm = currentArm;
  newArm = angles;
  HAL_transition();
}

// TODO smooth easy-in-easy-out
void HAL_transition()
{
  currentArm = newArm;  // TODO
  
  double upperArmServoAngle = currentArm.upper * UPPER_ARM_GEAR + UPPER_ARM_SERVO_TRIM;
  double upperDelta         = currentArm.upper - UPPER_ARM_ANGLE;

  double tmp1 = HAL_getAngleFromJointAngle(currentArm.lower);
  if (tmp1 == -1) {
    Serial.println("ERROR: lower");
    return;
  }

  // Calculate around middle (lever_lower_angle_middle = SERVO_MIDDLE_ANGLE)
  double lowerArmServoAngle = (tmp1 - lever_lower_angle_middle + upperDelta) * LOWER_ARM_GEAR + SERVO_MIDDLE_ANGLE + LOWER_ARM_SERVO_TRIM;
  double lowerDelta         = tmp1 - lever_lower_angle_middle;

  double tmp2 = HAL_getAngleFromJointAngle(currentArm.wrist);
  if (tmp2 == -1) {
    Serial.println("ERROR: wrist");
    return;
  }
  double wristServoAngle = 180 - ((tmp2 - lever_wrist_angle_middle + lowerDelta + upperDelta) * WRIST_GEAR + SERVO_MIDDLE_ANGLE + WRIST_SERVO_TRIM);

  Serial.print(currentArm.upper);
  Serial.print(" -> ");
  Serial.print(upperArmServoAngle);
  Serial.print("\t");
  Serial.print(currentArm.lower);
  Serial.print(" -> ");
  Serial.print(lowerArmServoAngle);
  Serial.print("\t");
  Serial.print(currentArm.wrist);
  Serial.print(" -> ");
  Serial.print(wristServoAngle);
  Serial.println();
  upperArmServo.writeMicroseconds(HAL_angleToMs(upperArmServoAngle));
  lowerArmServo.writeMicroseconds(HAL_angleToMs(lowerArmServoAngle));
  wristServo.writeMicroseconds(HAL_angleToMs(wristServoAngle));
}

uint16_t HAL_angleToMs(double angle)
{
  uint16_t servoMs = mapf(angle, 0, 180, SERVO_MIN, SERVO_MAX);

  if (servoMs < SERVO_MIN) servoMs = SERVO_MIN;
  if (servoMs > SERVO_MAX) servoMs = SERVO_MAX;

  return servoMs;
}


double HAL_getAngleFromJointAngle(double jointAngle)
{
  double e_sq = lever_d_sq + lever_a_sq - 2 * LEVER_D * LEVER_A * cos((180-jointAngle)*DEGTORAD);
  double e    = sqrt(e_sq);

  double cosang1 = (lever_d_sq + e_sq - lever_a_sq) / (2 * LEVER_D * e);
  double cosang2 = (e_sq + lever_c_sq - lever_b_sq) / (2 * e * LEVER_C);
//  Serial.println(e_sq);
//  Serial.println(e);
//  Serial.println(LEVER_D);
//  Serial.println(LEVER_C);
//  Serial.println(2 * LEVER_D * e);
//  Serial.println(2 * LEVER_C * e);
//  Serial.println(cosang1);
//  Serial.println(cosang2);

  if (abs(cosang1) > 1) {
    return -1;
  }

  if (abs(cosang2) > 1) {
    return -1;
  }

  return 90.0 - acos(cosang1)*RADTODEG + acos(cosang2)*RADTODEG;
}
