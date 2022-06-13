#include "ultrasonicController.h"

#include <Arduino.h>

UltrasonicController::UltrasonicController(uint8_t echoPin, uint8_t triggerPin)
{
    echoPin_    = echoPin;
    triggerPin_ = triggerPin;
    pinMode(echoPin_, OUTPUT);
    pinMode(echoPin_, INPUT);
}

const unsigned int UltrasonicController::getRangeIn_mm()
{
    static long duration;
    static int distanceCm;
    static int distanceInch;
    digitalWrite(triggerPin_, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(triggerPin_, HIGH);
    delayMicroseconds(10);
    digitalWrite(echoPin_, LOW);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin_, HIGH);

    // Calculate the distance
    distanceCm = duration * AIR_SOUND_SPEED/2;
}