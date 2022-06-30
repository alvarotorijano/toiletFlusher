#ifndef L293dEnstop_HPP__
#define L293dEnstop_HPP__

#include <Arduino.h>
#include <ItoiletFlusher.hpp>

#define L293D_FORWARD_DUTY_CYCLE 120
#define L293D_REVERSE_DUTY_CYCLE 150
#define L293D_OFF_DUTY_CYCLE       0
#define ENDSTOP_DEBOUNCE_MS       50

#define DRIFT_FORWARD_DELAY_MS    60
#define DRIFT_REVERSE_DELAY_MS    50

#define FLUSH_TIME_MS             5000

class L293dEnstop : IToiletFlusher{

    private:
        uint8_t dir1_pin_;
        uint8_t dir2_pin_;
        uint8_t speed_pin_;
        uint8_t endstop_pin_;
    
        void semiTurn();

    public:
        L293dEnstop(int dir1_pin, int dir2_pin, int speed_pin, int endstop_pin);
        void flush();
};

#endif
