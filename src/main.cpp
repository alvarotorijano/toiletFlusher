#include <Arduino.h>
//--------------------------------------------------------------------------------
// ESP32 & VL53L3CX test app by Motti Bazar.
// App utilizes the interrupt method.
// Code parts below that were developed by me can be used for non-commercial use
// but I am asking to be mentioned as the developer.
//
// 5-May-2021
//
// My ESP32 setup:
//  SDA   - pin 21
//  SCL   - pin 22
//  INT   - pin 32
//  XSHUT - pin 33
//--------------------------------------------------------------------------------

#include <Arduino.h>
#include <Wire.h>
//#include "VL53L3CXRangeMeter.hpp"
#include "L293dEnstop.hpp"
#include <catDetector.hpp>

#include "EventDispatcher.hpp"

#define  SERIAL_BAUD_RATE  115200


//IRangeMeter * rangeMeter = NULL;
L293dEnstop * toiletFlusher = nullptr;
CatDetector * catDetector_ = nullptr;

void setup(){
    Serial.begin(SERIAL_BAUD_RATE);
    Serial.println("Toilet Flusher");
    //rangeMeter = new VL53L3CX_RangeMeter();
    toiletFlusher = new L293dEnstop();
    catDetector_ = new CatDetector();
}

void loop(){
    //Serial.println(rangeMeter->getRangeIn_mm());
    //toiletFlusher->flush();
    //delay(1000);
}