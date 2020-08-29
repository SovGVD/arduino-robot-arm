#include "def.h"
#include "struct.h"
#include "cli.h"
#include "config.h"
#include <Servo.h>

Servo upperArmServo;
Servo lowerArmServo;
Servo wristServo;

double upperArmServoAngle = 90;

Stream *cliSerial;

void setup() {
  delay(500);

  Serial.begin(115200);
  cliSerial = &Serial;
  Serial.println("Robot Arm");
  initCLI();
  
  upperArmServo.attach(UPPER_ARM_SERVO_PIN);
  lowerArmServo.attach(LOWER_ARM_SERVO_PIN);
  wristServo.attach(WRIST_SERVO_PIN);

  // initial state
  HAL_setAngles({UPPER_ARM_ANGLE, LOWER_ARM_ANGLE, WRIST_ANGLE, GRIPPER_ANGLE});
  //upperArmServo.writeMicroseconds(1500);  // 0..90
}

void loop() {
  // put your main code here, to run repeatedly:
  updateCLI();

  delay(10);  // TODO timer

}
