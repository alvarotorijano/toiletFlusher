#include "AutoSulivansFeederController.hpp"

AutoSulivansFeederController::AutoSulivansFeederController()
{   
    delay(100);
    pinMode(BLUETOOTH_ENABLE_PIN, OUTPUT);
    disableBT();

    Serial2.begin(BLUETOOTH_BAUDRATE, BLUETOOTH_SERIAL_MODE, BLUETOOTH_RX_PIN, BLUETOOTH_TX_PIN);
    EventDispatcher::getInstance().subscribe(eventTypes::CAT_DETECTED, this);
    EventDispatcher::getInstance().subscribe(eventType_t::ALEXA_PRIZE_DELIVERY, this);
    
    xTaskCreate(
    launchAutosulivansTask,
    "autosulivansController_task",   // Name of the task (for debugging)
    2000,            // Stack size (bytes)
    this,            // Parameter to pass
    1,               // Task priority
    NULL             // Task handle
    );

}

void AutoSulivansFeederController::enableBT()
{
    digitalWrite(BLUETOOTH_ENABLE_PIN, HIGH);
}

void AutoSulivansFeederController::disableBT()
{
    digitalWrite(BLUETOOTH_ENABLE_PIN, LOW);
}

void AutoSulivansFeederController::dispenseFood()
{
    
    Serial.println("Delivering prizes");
    payPrizes_ = true;
}

void AutoSulivansFeederController::sendMessageLoop()
{
    while (true)
    {
        if (payPrizes_ == true)
        {   
            Serial.println("Started delivery process");
            //enableBT();
            delay((AUTOSULIVANS_CONNECTION_TIME > FOOD_DISPENSER_DELAY_MS) ? AUTOSULIVANS_CONNECTION_TIME: FOOD_DISPENSER_DELAY_MS);
            Serial2.println(AUTOSULIVANS_DELIVER_PRICE_COMMAND);
            payPrizes_ = false;
            //disableBT();
            Serial.println("Finished delivery process");
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
        case eventType_t::ALEXA_PRIZE_DELIVERY:
            dispenseFood();
            break;
    }
}

void launchAutosulivansTask(void *pvParameters)
{
    AutoSulivansFeederController * controller = (AutoSulivansFeederController *)pvParameters;
    controller->sendMessageLoop();
}