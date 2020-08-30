arm IK_getAngles(arm cArm, point cPoint)
{
  arm _arm = {-1, -1, cArm.wrist, cArm.gripper};
 
  /**
   * Angles:
   * 
   *          B_  <- lower arm
   *         /  -_
   *        /     -C <- wrist
   * upper /        \
   * arm  /          D <- point
   *  \  /
   * ___A___
   * ///////
   */

  double AD_sq = cPoint.x*cPoint.x + cPoint.y*cPoint.y;
  double AD    = sqrt(AD_sq);

  double BD_sq = lower_arm_l_sq + gripper_l_sq - 2 * LOWER_ARM_L * GRIPPER_L * dcos(90.0 + cArm.wrist);
  double BD    = sqrt(BD_sq);

  
  double cosA1 = (upper_arm_l_sq + AD_sq - BD_sq) / (2 * UPPER_ARM_L * AD);
  if (cosA1 < -1 || cosA1 > 1) {
    Serial.print("ERROR cosA1 ");
    Serial.println(cosA1);
    // ERROR
    return _arm;
  }
  _arm.upper = (acos(cosA1) + atan2(cPoint.y, cPoint.x)) * RADTODEG;

  double cosB1 = (upper_arm_l_sq + BD_sq - AD_sq) / (2 * UPPER_ARM_L * BD);
  if (cosB1 < -1 || cosB1 > 1) {
    Serial.print("ERROR cosB1 ");
    Serial.println(cosB1);
    // ERROR
    return _arm;
  }
  double cosB2 = (BD_sq + lower_arm_l_sq - gripper_l_sq) / (2 * BD * LOWER_ARM_L);
  if (cosB2 < -1 || cosB2 > 1) {
    Serial.print("ERROR cosB2 ");
    Serial.println(cosB2);

    // ERROR
    return _arm;    
  }

  if (_arm.wrist > 90) {
    _arm.lower = (acos(cosB1) - acos(cosB2)) * RADTODEG;
  } else {
    _arm.lower = (acos(cosB1) + acos(cosB2)) * RADTODEG;
  }

  Serial.print(_arm.upper);
  Serial.print("\t");
  Serial.print(_arm.lower);
  Serial.print("\t");
  Serial.print(_arm.wrist);
  Serial.println();
  
  return _arm;
}
