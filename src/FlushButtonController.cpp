#include "FlushButtonController.hpp"

FlushButtonController::FlushButtonController()
{
    // Initialize the pin
    pinMode(FLUSH_BUTTON_PIN, INPUT_PULLUP);
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
        if (last_state_ != digitalRead(FLUSH_BUTTON_PIN))
        {
            delay(FLUSH_BUTTON_DEBOUNCE_TIME_MS);

            if (last_state_ != digitalRead(FLUSH_BUTTON_PIN))
            {
                last_state_ = digitalRead(FLUSH_BUTTON_PIN);
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
    }
}

void buttonTask (void *pvParameters)
{
    FlushButtonController * flushButtonController = (FlushButtonController *)pvParameters;
    flushButtonController->buttonLoop();
}