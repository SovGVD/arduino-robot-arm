// PINs
#define UPPER_ARM_SERVO_PIN 7
#define LOWER_ARM_SERVO_PIN 8
#define WRIST_SERVO_PIN     6
#define GRIPPER_SERVO       5 // TODO

// Gear ratio
#define UPPER_ARM_GEAR 1.5
#define LOWER_ARM_GEAR 1.5
#define WRIST_GEAR     1.5
#define GRIPPER_GEAR   1  // TODO

// Levers
#define LEVER_A       30.0     // from Pivot point of lower arm to lever joint point
#define LEVER_B      134.0     // Lever
#define LEVER_C       42.4264  // Servo lever
#define UPPER_ARM_L  150.0     // length of upper arm
#define LOWER_ARM_L  140.0     // length on lower arm
#define GRIPPER_L     30.0     // length of gripper from joint to finger tip

// Servo limits
#define SERVO_MIN  500  // ms
#define SERVO_MID 1500  // ms
#define SERVO_MAX 2500  // ms

// Servo trim
#define UPPER_ARM_SERVO_TRIM 0.0
#define LOWER_ARM_SERVO_TRIM 0.0
#define WRIST_SERVO_TRIM     0.0

// Initial state
/**
 *                _*== [0...180]
 *           _ --
 *         /*
 *        / lower_angle [0...180]
 *       /
 *      /
 *     / upper_agle [0...90]
 *  ~~*~~~
 * 
 * 
 */

#define SERVO_MIDDLE_ANGLE 90

#define UPPER_ARM_ANGLE 90
#define LOWER_ARM_ANGLE 90
#define WRIST_ANGLE 90

// Initial position of gripper
#define START_X       170.0  // length of lower arm + gripper
#define START_Y       150.0  // length of upper arm
#define GRIPPER_ANGLE 180    // 0 - closed, 180 - open
