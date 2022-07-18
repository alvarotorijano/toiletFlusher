#include "VL53L3CXRangeMeter.hpp"

VL53L3CX_RangeMeter::VL53L3CX_RangeMeter(){
    Serial.println("Try to initialize: ");
    vl53lxWrapper_ = new Vl53lxWrapper(VL53L3CX_XSHUT_PIN, VL53L3CX_INTERRUPT_PIN, VL53L3CX_ADDRESS, SDA_PIN, SCL_PIN);
    Serial.println("Initialized");
    //Start the thread
}

const float VL53L3CX_RangeMeter::getRangeIn_mm() { 
    VL53LX_MultiRangingData_t measurement = vl53lxWrapper_->getLatestMeasurement();
    return (float) measurement.RangeData->RangeMilliMeter;
}

const float VL53L3CX_RangeMeter::getRangeIn_cm() { 
    return getRangeIn_mm() / 10;
}
