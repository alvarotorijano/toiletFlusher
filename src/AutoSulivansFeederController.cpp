#include "AutoSulivansFeederController.hpp"

AutoSulivansFeederController::AutoSulivansFeederController()
{
    Serial2.begin(BLUETOOTH_BAUDRATE, BLUETOOTH_SERIAL_MODE, BLUETOOTH_RX_PIN, BLUETOOTH_TX_PIN);
    EventDispatcher::getInstance().subscribe(eventTypes::CAT_DETECTED, this);

    xTaskCreate(
    launchAutosulivansTask,
    "autosulivansController_task",   // Name of the task (for debugging)
    2000,            // Stack size (bytes)
    this,            // Parameter to pass
    1,               // Task priority
    NULL             // Task handle
    );

}

void AutoSulivansFeederController::dispenseFood()
{
    payPrizes_ = true;
}

void AutoSulivansFeederController::sendMessageLoop()
{
    while (true)
    {
        if (payPrizes_ == true)
        {
            delay(FOOD_DISPENSER_DELAY_MS);
            Serial2.println(AUTOSULIVANS_PRIZE_MESSAGE);
            payPrizes_ = false;
        }
        while (Serial2.available())
        {
            Serial2.read();
        }
        delay(5);
    }
}

void AutoSulivansFeederController::onEvent(Event event)
{
    switch(event.eventType){
        case eventTypes::CAT_DETECTED:
            dispenseFood();
            break;
    }
}

void launchAutosulivansTask(void *pvParameters)
{
    AutoSulivansFeederController * controller = (AutoSulivansFeederController *)pvParameters;
    controller->sendMessageLoop();
}