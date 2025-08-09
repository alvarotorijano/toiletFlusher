#include "config.h"

const unsigned int SERIAL_BAUDRATE =                115200;

#define VL53L3CX
//const unsigned int ULTRASONIC

const unsigned int CAT_MIN_DISTANCE =               200;
const unsigned int CAT_MAX_DISTANCE =               500;

const unsigned int CAT_MIN_TOILET_TIME =            10000;
const unsigned int CAT_MAX_TOILET_TIME =            35000;

const unsigned int FLUSH_LED_PWM_FRECUENCY =        1000;
const unsigned int FLUSH_LED_PWM_CHANNEL =          0;
const unsigned int FLUSH_LED_PWM_RESOLUTION =       8;
const unsigned int MAX_PWM_LED_DUTY_CYCLE =         255;
const unsigned int FADE_LED_PERIOD_MS =             1000;
const unsigned int BLINK_LED_PERIOD_MS =            100;
const unsigned int BLINK_LED_TIME_MS =              1000;

const unsigned int FLUSH_BUTTON_DEBOUNCE_TIME_MS =  50;

const unsigned int BLUETOOTH_SERIAL_MODE =          SERIAL_8N1;
const unsigned int BLUETOOTH_BAUDRATE =             9600;

const unsigned int FOOD_DISPENSER_DELAY_MS =        10000;

// Define the variables that are declared as extern in config.h
const char* ALEXA_FLUSHER_SPOKEN_NAME = "cisterna";
const char* ALEXA_PRIZE_DEVILER_SPOKEN_NAME = "premios";

const char* ssid = "HackFi";
const char* password = "12345678900";

const char* MQTT_SERVER = "192.168.1.148";
const char* MQTT_USER = "MQTT_AT";
const char* MQTT_PASSWORD = "MQTT_AT";
