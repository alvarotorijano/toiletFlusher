#ifndef FLUSH_BUTTON_CONTROLLER_HPP__
#define FLUSH_BUTTON_CONTROLLER_HPP__

#include "Arduino.h"
#include "pins.h"
#include "config.h"
#include "EventDispatcher.hpp"
#include <esp_task_wdt.h>

class FlushButtonController 
{
    
    public:
        FlushButtonController(int pin);
        FlushButtonController(int pin, eventType_t pressEvent, eventType_t releaseEvent);
        void buttonLoop();

    private:
        int pin_;
        bool last_state_;
        eventType_t pressEvent_;
        eventType_t releaseEvent_;
};

void buttonTask (void *pvParameters);

#endif