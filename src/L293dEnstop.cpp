#include "L293dEnstop.hpp"

L293dEnstop::L293dEnstop(int dir1_pin, int dir2_pin, int speed_pin, int endstop_pin){
    dir1_pin_ = dir1_pin;
    dir2_pin_ = dir2_pin;
    speed_pin_ = speed_pin;
    endstop_pin_ = endstop_pin;

    pinMode(speed_pin_, OUTPUT);
    pinMode(dir1_pin_, OUTPUT);
    pinMode(dir2_pin_, OUTPUT);
    pinMode(endstop_pin_, INPUT_PULLUP);

    digitalWrite(dir1_pin_, HIGH);
    digitalWrite(dir2_pin_, LOW);
}

void L293dEnstop::semiTurn(){

    digitalWrite(dir1_pin_, HIGH);
    digitalWrite(dir2_pin_, LOW);

    analogWrite(speed_pin_, L293D_FORWARD_DUTY_CYCLE);

    while(digitalRead(endstop_pin_)==LOW){
        delay(ENDSTOP_DEBOUNCE_MS);
    }
    while(digitalRead(endstop_pin_)==HIGH){
        delay(ENDSTOP_DEBOUNCE_MS);
    }

    delay(DRIFT_FORWARD_DELAY_MS);

    digitalWrite(dir1_pin_, LOW);
    digitalWrite(dir2_pin_, HIGH);

    analogWrite(speed_pin_, L293D_REVERSE_DUTY_CYCLE);
    delay(DRIFT_REVERSE_DELAY_MS);

    digitalWrite(dir1_pin_, LOW);
    digitalWrite(dir2_pin_, LOW);
    analogWrite(speed_pin_, L293D_OFF_DUTY_CYCLE);
}

void L293dEnstop::flush(){
    semiTurn();
    delay(FLUSH_TIME_MS);
    semiTurn();
}