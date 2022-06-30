#ifndef ULTRASONIC_CONTROLLER__
#define ULTRASONIC_CONTROLLER__

#include "IRangeMeter.hpp"
#include <cstdint>

#define AIR_SOUND_SPEED     0.343f // mm/uS
#define WATER_SOUND_SPEED   1.480f // mm/uS 

class UltrasonicController : IRangeMeter
{

private:
    uint8_t echoPin_;
    uint8_t triggerPin_;
    float  soundSpeed_;

public:
    UltrasonicController(uint8_t echoPin, uint8_t triggerPin, bool water = false);
    const float getRangeIn_mm();
    const float getRangeIn_cm();
};

#endif