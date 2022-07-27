#ifndef CONFIG_H__
#define CONFIG_H__

//#define DEBUG_RANGE_METER

#define SERIAL_BAUDRATE 115200

#define VL53L3CX
//#define ULTRASONIC

#define CAT_MIN_DISTANCE 100
#define CAT_MAX_DISTANCE 200

#define CAT_MIN_TOILET_TIME 5000
#define CAT_MAX_TOILET_TIME 10000

#define FLUSH_LED_PWM_FRECUENCY       1000
#define FLUSH_LED_PWM_CHANNEL         0
#define FLUSH_LED_PWM_RESOLUTION      8
#define MAX_PWM_LED_DUTY_CYCLE        255
#define FADE_LED_PERIOD_MS            1000
#define BLINK_LED_PERIOD_MS           100
#define BLINK_LED_TIME_MS             1000

#define FLUSH_BUTTON_DEBOUNCE_TIME_MS 50

#define BLUETOOTH_SERIAL_MODE         SERIAL_8N1
#define BLUETOOTH_BAUDRATE            9600

#define FOOD_DISPENSER_DELAY_MS       5000

#include <configSanitizer.h>
#endif