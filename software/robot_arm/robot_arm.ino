#include "def.h"
#include "struct.h"
#include "cli.h"
#include "config.h"
#include <Servo.h>

Servo upperArmServo;
Servo lowerArmServo;
Servo wristServo;

double upperArmServoAngle = 90;

arm previousArm = {0, 0, WRIST_ANGLE, GRIPPER_ANGLE};
arm currentArm  = {0, 0, WRIST_ANGLE, GRIPPER_ANGLE};
arm newArm      = {0, 0, WRIST_ANGLE, GRIPPER_ANGLE};

point gripperPos = {START_X, START_Y};

double lever_a_sq     = LEVER_A*LEVER_A;
double lever_b_sq     = LEVER_B*LEVER_B;
double lever_c_sq     = LEVER_C*LEVER_C;
double upper_arm_l_sq = UPPER_ARM_L*UPPER_ARM_L;
double lower_arm_l_sq = LOWER_ARM_L*LOWER_ARM_L;
double gripper_l_sq   = GRIPPER_L*GRIPPER_L;

uint8_t activeTest = 0;
double testIteration = 0;


Stream *cliSerial;

void setup() {
  delay(500);

  previousArm = IK_getAngles(previousArm, gripperPos);
  currentArm  = IK_getAngles(currentArm, gripperPos);
  newArm      = IK_getAngles(newArm, gripperPos);

  Serial.begin(115200);
  cliSerial = &Serial;
  Serial.println("Robot Arm");
  initCLI();
  
  upperArmServo.attach(UPPER_ARM_SERVO_PIN);
  lowerArmServo.attach(LOWER_ARM_SERVO_PIN);
  wristServo.attach(WRIST_SERVO_PIN);

  // initial state
  HAL_setAngles(newArm);
}

void loop() {
  // put your main code here, to run repeatedly:
  updateCLI();
  doTests();

  delay(10);  // TODO timer

}
