#ifndef AUTOSULIVANS_FEEDER_CONTROLLER_HPP__
#define AUTOSULIVANS_FEEDER_CONTROLLER_HPP__

#include "arduino.h"
#include "IFoodDispenser.hpp"
#include "pins.h"
#include "config.h"
#include "EventDispatcher.hpp"

#define AUTOSULIVANS_CONNECTION_TIME 3000
#define AUTOSULIVANS_DELIVER_PRICE_COMMAND "test"

class AutoSulivansFeederController : public IFoodDispenser, public Subscriber
{
    public:
        AutoSulivansFeederController();
        void onEvent(Event event);
        void dispenseFood();
        void sendMessageLoop();
        void enableBT();
        void disableBT();

    private:
        bool payPrizes_ = false;
};

void launchAutosulivansTask(void *pvParameters);

#endif