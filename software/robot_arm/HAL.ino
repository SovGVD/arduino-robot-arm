
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
  if (angleId == WRIST) {
    // Changing wrist angle should recalculate all angles
    newArm = IK_getAngles(newArm, gripperPos);
  }
  HAL_transition();  
}

void HAL_setPositionByAxis(uint8_t axisId, double value)
{
  point _point = {gripperPos.x, gripperPos.y};
  
  switch(axisId) {
    case POINT_X:
      _point.x = value;
      break;
    case POINT_Y:
      _point.y = value;
      break;
  }

  HAL_setPosition(_point);
}

void HAL_setPosition(point _point)
{
  gripperPos = _point;
  HAL_setAngles(IK_getAngles(currentArm, _point));  
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
  double e_sq = upper_arm_l_sq + lever_a_sq - 2 * UPPER_ARM_L * LEVER_A * cos((180-jointAngle)*DEGTORAD);
  double e    = sqrt(e_sq);

  double cosang1 = (upper_arm_l_sq + e_sq - lever_a_sq) / (2 * UPPER_ARM_L * e);
  double cosang2 = (e_sq + lever_c_sq - lever_b_sq) / (2 * e * LEVER_C);

  if (abs(cosang1) > 1) {
    return -1;
  }

  if (abs(cosang2) > 1) {
    return -1;
  }

  return 90.0 - acos(cosang1)*RADTODEG + acos(cosang2)*RADTODEG;
}
