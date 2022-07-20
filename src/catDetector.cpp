#include <catDetector.hpp>

CatDetector::CatDetector() :

    #ifdef VL53L3CX
    rangeMeter_(new VL53L3CX_RangeMeter())
    #endif
    
    #ifdef ULTRASONIC
    rangeMeter_(new UltrasonicController())
    #endif

{

    xTaskCreate(
    launchCatDetectorTask,
    "detectCat_task",   // Name of the task (for debugging)
    2000,            // Stack size (bytes)
    this,            // Parameter to pass
    1,               // Task priority
    NULL             // Task handle
    );
    
}

void CatDetector::detectCat() {
bool searching = false;
    unsigned long lastDetectionTime = 0;
    float distance = 0;
    while (true){
        distance = rangeMeter_->getRangeIn_mm();
        #ifdef DEBUG_RANGE_METER
            Serial.println("Distance sensor: " + String(distance));
        #endif
        if (distance > CAT_MIN_DISTANCE && distance < CAT_MAX_DISTANCE)
        {
            if (!searching) 
            {
                lastDetectionTime = millis();
                searching = true;
            }
            else
            {
                #ifdef DEBUG_RANGE_METER
                    Serial.println("Time passing");
                #endif
            }
        }
        else 
        {
            if ((searching) && !(distance > CAT_MIN_DISTANCE && distance < CAT_MAX_DISTANCE))
            {
                
                if ((millis() - lastDetectionTime > CAT_MIN_TOILET_TIME) 
                    && (millis() - lastDetectionTime < CAT_MAX_TOILET_TIME)) 
                {
                    // cat detected
                    Serial.println("Cat detected");
                    #ifdef DEBUG_RANGE_METER
                        delay(1000);
                    #endif
                    searching = false;
                    lastDetectionTime = 0;
                    onCatDetected();
                }
                else 
                {
                    // cat not detected
                    Serial.println("Cat not detected");
                    #ifdef DEBUG_RANGE_METER
                        delay(1000);
                    #endif
                    searching = false;
                    lastDetectionTime = 0;
                    onCatNotDetected();
                }
            }
        }
    }
}

void CatDetector::onCatDetected() {
    Event event;
    event.eventType = CAT_DETECTED;
    
    EventDispatcher & dispatcher = EventDispatcher::getInstance();
    dispatcher.sendEvent(event);
}

void CatDetector::onCatNotDetected() {
    Event event;
    event.eventType = CAT_NOT_DETECTED;
    
    EventDispatcher & dispatcher = EventDispatcher::getInstance();
    dispatcher.sendEvent(event);
}

void launchCatDetectorTask(void * pvParameters)
{
    CatDetector * catDetector = (CatDetector *)pvParameters;
    catDetector->detectCat();
    
}