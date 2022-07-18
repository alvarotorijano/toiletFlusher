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

    CatDetector::CatDetector() :

    //actionOnDetect_ = actionOnDetect;
    Serial.println("Toilet Flusher");
    xTaskCreate(
    launchTouletFlusherTask,
    "detectCat_task",   // Name of the task (for debugging)
    2000,            // Stack size (bytes)
    this,            // Parameter to pass
    1,               // Task priority
    NULL             // Task handle
    );

}

void launchTouletFlusherTask(void *pvParameters) {
    L293dEnstop * toiletFlusher = (L293dEnstop *)pvParameters;
}

void L293dEnstop::semiTurn(){

    digitalWrite(dir1_pin_, HIGH);
    digitalWrite(dir2_pin_, LOW);

    analogWrite(speed_pin_, L293D_FORWARD_DUTY_CYCLE);

    while(digitalRead(endstop_pin_)==LOW){
        delay(L293D_ENDSTOP_DEBOUNCE_MS);
    }
    while(digitalRead(endstop_pin_)==HIGH){
        delay(L293D_ENDSTOP_DEBOUNCE_MS);
    }

    delay(L293D_DRIFT_FORWARD_DELAY_MS);

    digitalWrite(dir1_pin_, LOW);
    digitalWrite(dir2_pin_, HIGH);

    analogWrite(speed_pin_, L293D_REVERSE_DUTY_CYCLE);
    delay(L293D_DRIFT_REVERSE_DELAY_MS);

    digitalWrite(dir1_pin_, LOW);
    digitalWrite(dir2_pin_, LOW);
    analogWrite(speed_pin_, L293D_OFF_DUTY_CYCLE);

    delay(L293D_ENDSTOP_DEBOUNCE_MS);
}

void L293dEnstop::flush(){
    semiTurn();
    if(digitalRead(endstop_pin_)==HIGH){
        semiTurn();
        Serial.println("Misturn");
    }
    delay(L293D_FLUSH_TIME_MS);
    semiTurn();
    if(digitalRead(endstop_pin_)==HIGH){
        semiTurn();
        Serial.println("Misturn");
    }
    Serial.println("Flush finished");
}