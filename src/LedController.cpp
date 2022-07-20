#include "LedController.hpp"

LedController::LedController(){
    ledcSetup(FLUSH_LED_PWM_CHANNEL, FLUSH_LED_PWM_FRECUENCY, FLUSH_LED_PWM_RESOLUTION);
    ledcAttachPin(FLUSH_BUTTON_LED_PIN, FLUSH_LED_PWM_CHANNEL);
    ledcWrite(FLUSH_LED_PWM_CHANNEL, 0);

    EventDispatcher::getInstance().subscribe(eventTypes::FLUSH_STARTED, this);
    EventDispatcher::getInstance().subscribe(eventTypes::FLUSH_FINISHED, this);
    EventDispatcher::getInstance().subscribe(eventTypes::FLUSH_BUTTON_PUSHED, this);
    EventDispatcher::getInstance().subscribe(eventTypes::FLUSH_BUTTON_RELEASED, this);
    EventDispatcher::getInstance().subscribe(eventTypes::CAT_NOT_DETECTED, this);

    state_ = LedState::OFF;

    xTaskCreate(
    ledTask,
    "led_task",   // Name of the task (for debugging)
    5000,            // Stack size (bytes)
    this,            // Parameter to pass
    1,               // Task priority
    NULL             // Task handle
    );
}

void ledTask(void *pvParameters)
{
    LedController * ledController = (LedController *)pvParameters;
    ledController->ledLoop();
}

void LedController::ledLoop()
{
    static LedState lastState = LedState::OFF;
    int i = 0;
    while (true)
    {   

        if (lastState != state_)
        {
            lastState = state_;
            last_effect_time_ = millis();
            switch (state_)
            {
                case LedState::OFF:
                    setLedOFF();
                    break;
                case LedState::ON:
                    setLedON();
                    break;
                case LedState::BLINKING:
                    blink();
                    break;
                case LedState::FADING:
                    fade();
                    break;
            }
        }
        
        if (state_ == LedState::BLINKING || state_ == LedState::FADING)
        {
            switch (state_)
            {
                case LedState::BLINKING:
                    blink();
                    break;
                case LedState::FADING:
                    fade();
                    break;
            }
        }
        delay(5);
    }
}

void LedController::onEvent (Event event) {

    switch(event.eventType){
        case eventTypes::FLUSH_BUTTON_PUSHED:
            state_ = LedState::ON;
            break;

        case eventTypes::FLUSH_BUTTON_RELEASED:
            if (state_ == LedState::ON)
            {
                state_ = LedState::OFF;
            }
            break;

        case eventTypes::FLUSH_STARTED:
            state_ = LedState::FADING;
            break;

        case eventTypes::FLUSH_FINISHED:
            state_ = LedState::OFF;
            break;

        case eventTypes::CAT_NOT_DETECTED:
            state_ = LedState::BLINKING;
            break;
           
        default:
            break;
    }
}

void LedController::setLedON()
{   
    ledcWrite(FLUSH_LED_PWM_CHANNEL, MAX_PWM_LED_DUTY_CYCLE);
}

void LedController::setLedOFF()
{   
    ledcWrite(FLUSH_LED_PWM_CHANNEL, 0);
}

void LedController::fade()
{   
    static unsigned long moment = millis() - last_effect_time_;
    moment = millis() - last_effect_time_;
    ledcWrite(FLUSH_LED_PWM_CHANNEL, MAX_PWM_LED_DUTY_CYCLE * abs(sin(moment/(FADE_LED_PERIOD_MS / PI))));
}

void LedController::blink()
{   
    static unsigned long moment = millis() - last_effect_time_;
    moment = millis() - last_effect_time_;
    ledcWrite(FLUSH_LED_PWM_CHANNEL, MAX_PWM_LED_DUTY_CYCLE * ((moment % BLINK_LED_PERIOD_MS) < (BLINK_LED_PERIOD_MS / 2) ? 1 : 0));

    if (moment > BLINK_LED_TIME_MS)
    {
        state_ = LedState::OFF;
    }

}