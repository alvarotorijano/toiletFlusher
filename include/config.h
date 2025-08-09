#ifndef CONFIG_H__
#define CONFIG_H__

#include "arduino.h"

//#define DEBUG_RANGE_METER

extern const unsigned int SERIAL_BAUDRATE;

#define VL53L3CX
//#define ULTRASONIC

extern const unsigned int CAT_MIN_DISTANCE;
extern const unsigned int CAT_MAX_DISTANCE;

extern const unsigned int CAT_MIN_TOILET_TIME;
extern const unsigned int CAT_MAX_TOILET_TIME;

extern const unsigned int FLUSH_LED_PWM_FRECUENCY;
extern const unsigned int FLUSH_LED_PWM_CHANNEL;
extern const unsigned int FLUSH_LED_PWM_RESOLUTION;
extern const unsigned int MAX_PWM_LED_DUTY_CYCLE;
extern const unsigned int FADE_LED_PERIOD_MS;
extern const unsigned int BLINK_LED_PERIOD_MS;
extern const unsigned int BLINK_LED_TIME_MS;

extern const unsigned int FLUSH_BUTTON_DEBOUNCE_TIME_MS;

extern const unsigned int BLUETOOTH_SERIAL_MODE;
extern const unsigned int BLUETOOTH_BAUDRATE;

extern const unsigned int FOOD_DISPENSER_DELAY_MS;

extern const char* ALEXA_FLUSHER_SPOKEN_NAME;
extern const char* ALEXA_PRIZE_DEVILER_SPOKEN_NAME;

extern const char* ssid;
extern const char* password;

extern const char* MQTT_SERVER;
extern const char* MQTT_USER;
extern const char* MQTT_PASSWORD;


#include <configSanitizer.h>
#endif