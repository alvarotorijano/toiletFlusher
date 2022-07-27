#include "AutoSulivansFeederController.hpp"

AutoSulivansFeederController::AutoSulivansFeederController()
{
    Serial2.begin(BLUETOOTH_BAUDRATE, BLUETOOTH_SERIAL_MODE, BLUETOOTH_RX_PIN, BLUETOOTH_TX_PIN);
    EventDispatcher::getInstance().subscribe(eventTypes::FLUSH_FINISHED, this);
}

void AutoSulivansFeederController::dispenseFood()
{
    delay(FOOD_DISPENSER_DELAY_MS);
    Serial2.println(AUTOSULIVANS_PRIZE_MESSAGE);
}

void AutoSulivansFeederController::onEvent(eventTypes eventType, void *eventData)
{
    switch(eventType){
        case CAT_DETECTED:
            dispenseFood();
            break;
    }
}
