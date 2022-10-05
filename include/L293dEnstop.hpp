#ifndef L293dEnstop_HPP__
#define L293dEnstop_HPP__

#include <Arduino.h>
#include <ItoiletFlusher.hpp>
#include "pins.h"
#include "eventDispatcher.hpp"



#define L293D_FORWARD_DUTY_CYCLE 120
#define L293D_REVERSE_DUTY_CYCLE 150
#define L293D_OFF_DUTY_CYCLE       0

#define L293D_DRIFT_FORWARD_DELAY_MS    65
#define L293D_DRIFT_REVERSE_DELAY_MS    50

#define L293D_START_DEBOUNCE_MS         50
#define L293D_ENDSTOP_DEBOUNCE_MS       5
#define L293D_FLUSH_TIME_MS             5000

#define L293D_END_CYCLE_DEBOUNCE_MS     300

class L293dEnstop : public Subscriber, public IToiletFlusher{

    private:
        uint8_t dir1_pin_;
        uint8_t dir2_pin_;
        uint8_t speed_pin_;
        uint8_t endstop_pin_;
        bool flushEnabled_ = false;

        void semiTurn();

    protected:
        

    public:
        void flushLoop();
        void onEvent(Event event);
        L293dEnstop(int dir1_pin = L293D_MOTOR_DIRECTION1_PIN, int dir2_pin = L293D_MOTOR_DIRECTION2_PIN, int speed_pin = L293D_MOTOR_SPEED_PIN, int endstop_pin = L293D_POS_ENDSTOP_PIN);
        void flush();
};

void launchTouletFlusherTask(void *pvParameters);

#endif
