#include "FlushButtonController.hpp"

FlushButtonController::FlushButtonController(int pin): pin_(pin)
{
    // Initialize the pin
    pinMode(pin_, INPUT_PULLUP);
    last_state_ = HIGH;
    pressEvent_ = FLUSH_BUTTON_PUSHED;
    releaseEvent_ = FLUSH_BUTTON_RELEASED;
    
    xTaskCreate(
    buttonTask,
    "button_task",   // Name of the task (for debugging)
    2000,            // Stack size (bytes)
    this,            // Parameter to pass
    1,               // Task priority
    NULL             // Task handle
    );
}

FlushButtonController::FlushButtonController(int pin, eventType_t pressEvent, eventType_t releaseEvent) 
: pin_(pin), pressEvent_(pressEvent), releaseEvent_(releaseEvent)  
{
    // Initialize the pin
    pinMode(pin_, INPUT_PULLUP);
    last_state_ = HIGH;

    xTaskCreate(
    buttonTask,
    "button_task",   // Name of the task (for debugging)
    2000,            // Stack size (bytes)
    this,            // Parameter to pass
    1,               // Task priority
    NULL             // Task handle
    );
}


void FlushButtonController::buttonLoop()
{
    Event event;
    event.eventData = nullptr;
    while (true)
    {
        if (last_state_ != digitalRead(pin_))
        {
            delay(FLUSH_BUTTON_DEBOUNCE_TIME_MS);

            if (last_state_ != digitalRead(pin_))
            {
                last_state_ = digitalRead(pin_);
                if (last_state_ == LOW)
                {
                    Serial.println("Button pressed");

                    event.eventType = FLUSH_BUTTON_PUSHED;
                    EventDispatcher::getInstance().sendEvent(event);
                }
                else
                {
                    Serial.println("Button released");
                    
                    event.eventType = FLUSH_BUTTON_RELEASED;
                    EventDispatcher::getInstance().sendEvent(event);
                }
            }
        }
        esp_task_wdt_reset();
        taskYIELD();
    }
}

void buttonTask (void *pvParameters)
{
    FlushButtonController * flushButtonController = (FlushButtonController *)pvParameters;
    flushButtonController->buttonLoop();
}