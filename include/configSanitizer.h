#ifndef CONIF_SANITIZER_H__
#define CONIF_SANITIZER_H__

//Range meter sanitizer
    #ifdef VL53L3CX
        #ifdef ULTRASONIC
            #error "Only one of VL53L3CX or ULTRASONIC can be defined"
        #endif
    #endif

    #ifndef VL53L3CX
        #ifndef ULTRASONIC
            #error "Enable one of VL53L3CX or ULTRASONIC"
        #endif
    #endif

#endif