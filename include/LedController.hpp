#ifndef LED_CONTROLLER_HPP__
#define LED_CONTROLLER_HPP__

#include <Arduino.h>
#include "pins.h"
#include "config.h"
#include "EventDispatcher.hpp"


enum LedState{
    OFF,
    ON,
    BLINKING,
    FADING
};

class LedController : public Subscriber
{
    public:
        LedController();
        void onEvent(Event event);
        void ledLoop();
    
    private:
        enum LedState state;
        void setLedON();
        void setLedOFF();
        void blink();
        void fade();

        unsigned long last_effect_time_ = 0;

        enum LedState state_;
};

void ledTask(void *pvParameters);

#endif // LED_CONTROLLER_HPP__
