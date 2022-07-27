#ifndef AUTOSULIVANS_FEEDER_CONTROLLER_HPP__
#define AUTOSULIVANS_FEEDER_CONTROLLER_HPP__

#include "arduino.h"
#include "IFoodDispenser.hpp"
#include "pins.h"
#include "config.h"
#include "EventDispatcher.hpp"

#define AUTOSULIVANS_PRIZE_MESSAGE "test"

class AutoSulivansFeederController : private IFoodDispenser, public Subscriber
{
    public:
        AutoSulivansFeederController();
        void onEvent(eventTypes eventType, void *eventData);

    private:
        void dispenseFood();

};

void autosulivansTask(void *pvParameters);

#endif