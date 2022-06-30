#include "ultrasonicController.hpp"
#include <Arduino.h>

UltrasonicController::UltrasonicController(uint8_t echoPin, uint8_t triggerPin, bool water)
{
    echoPin_    = echoPin;
    triggerPin_ = triggerPin;
    pinMode(triggerPin_, OUTPUT);
    pinMode(echoPin_,    INPUT);

    if (water)
    {
        soundSpeed_ = WATER_SOUND_SPEED;
    }
    else
    {
        soundSpeed_ = AIR_SOUND_SPEED;
    }

}

const float UltrasonicController::getRangeIn_mm()
{
    static long duration;
    static float distance_mm;

    digitalWrite(triggerPin_, LOW);
    delayMicroseconds(2);
    
    // Sets the triggerPin_ on HIGH state for 10 micro seconds.
    // Sends the pulse
    digitalWrite(triggerPin_, HIGH);
    delayMicroseconds(10);
    digitalWrite(echoPin_, LOW);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin_, HIGH);

    // Calculate the distance
    distance_mm = duration * soundSpeed_ /2;
    
    return distance_mm;
}

// this function is used to get the distance in cm
// gets nothing and uses AIR_SOUND_SPEED
const float UltrasonicController::getRangeIn_cm()
{
    return getRangeIn_mm() / 10;
}