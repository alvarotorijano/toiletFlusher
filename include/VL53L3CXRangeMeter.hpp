#ifndef VL53L3CX_RANGE_METER_HPP__
#define VL53L3CX_RANGE_METER_HPP__

#include "IRangeMeter.hpp"
#include "pins.h"
#include "Vl53lxWrapper.h"

class VL53L3CX_RangeMeter : public IRangeMeter {
    public:
        VL53L3CX_RangeMeter();
        const float getRangeIn_mm();
        const float getRangeIn_cm();

    private:
        Vl53lxWrapper *vl53lxWrapper_ = NULL;

};


#endif // VL53L3CX_RANGE_METER_HPP__