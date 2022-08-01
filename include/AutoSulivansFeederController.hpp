#ifndef AUTOSULIVANS_FEEDER_CONTROLLER_HPP__
#define AUTOSULIVANS_FEEDER_CONTROLLER_HPP__

#include "arduino.h"
#include "IFoodDispenser.hpp"
#include "pins.h"
#include "config.h"
#include "EventDispatcher.hpp"

#define AUTOSULIVANS_PRIZE_MESSAGE "test"

class AutoSulivansFeederController : public IFoodDispenser, public Subscriber
{
    public:
        AutoSulivansFeederController();
        void onEvent(Event event);
        void dispenseFood();
        void sendMessageLoop();

    private:
        bool payPrizes_ = false;
};

void launchAutosulivansTask(void *pvParameters);

#endif