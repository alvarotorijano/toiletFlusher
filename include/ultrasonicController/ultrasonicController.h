#ifndef ULTRASONIC_CONTROLLER__
#define ULTRASONIC_CONTROLLER__

#include <cstdint>

#define AIR_SOUND_SPEED 0.343 // mm/uS

class UltrasonicController
{

private:
    uint8_t echoPin_;
    uint8_t triggerPin_;

public:
    UltrasonicController(uint8_t echoPin, uint8_t triggerPin);
    const unsigned int getRangeIn_mm();
};

#endif