#ifndef FLUSH_BUTTON_CONTROLLER_HPP__
#define FLUSH_BUTTON_CONTROLLER_HPP__

#include "Arduino.h"
#include "pins.h"
#include "config.h"
#include "EventDispatcher.hpp"

class FlushButtonController 
{
    public:
        FlushButtonController();
        void buttonLoop();

    private:
        bool last_state_;
};

void buttonTask (void *pvParameters);

#endif