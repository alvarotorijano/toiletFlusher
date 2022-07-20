#ifndef PINS_H__
#define PINS_H__

#define ULTRASONIC_ECHO_PIN     27
#define ULTRASONIC_TRIGGER_PIN  12

#define VL53L3CX_ADDRESS        0x12
#define VL53L3CX_XSHUT_PIN      33
#define VL53L3CX_INTERRUPT_PIN  32

#define SDA_PIN                 21
#define SCL_PIN                 22

#define LED_PIN                  2

/*/
#ifndef LED_BUILTIN
#define LED_BUILTIN LED_PIN
#endif 
//*/

#define L293D_MOTOR_SPEED_PIN         23
#define L293D_MOTOR_DIRECTION1_PIN    25
#define L293D_MOTOR_DIRECTION2_PIN    26
#define L293D_POS_ENDSTOP_PIN         27


#define FLUSH_BUTTON_LED_PIN          14

#define FLUSH_BUTTON_PIN              15

#endif