#ifndef CAT_DETECTOR_HPP__
#define CAT_DETECTOR_HPP__

#include <config.h>
#include <EventDispatcher.hpp>
#include <IRangeMeter.hpp> //this only kames this explicit because it is included in all the rangeMeter headers
#include <VL53L3CXRangeMeter.hpp>
#include <ultrasonicController.hpp>

#define DEBUG_RANGE_METER

class CatDetector {
    public:
        CatDetector();
        void detectCat();  
        void onCatDetected();
        void onCatNotDetected();
        IRangeMeter * rangeMeter_ = nullptr;
};

void launchCatDetectorTask(void * pvParameters);
void anotherTask(void * pvParameters) ;

#endif // CAT_DETECTOR_HPP__