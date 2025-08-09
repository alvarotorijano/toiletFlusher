#include <Arduino.h>

#define DEBUG_RANGE_METER
#define DEBUG_MQTT

#include <Wire.h>
//#include "VL53L3CXRangeMeter.hpp"
#include "L293dEnstop.hpp"
#include <catDetector.hpp>
#include "EventDispatcher.hpp"
#include "ledController.hpp"
#include "flushButtonController.hpp"
#include "AutoSulivansFeederController.hpp"
#include "AlexaEventSender.hpp"
#include "config.h"
#include "pins.h"
#include "wifiConfig.h"
#include "MQTT_Manager.hpp"

#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif

#define  SERIAL_BAUD_RATE  115200

//IRangeMeter * rangeMeter = NULL;
L293dEnstop * toiletFlusher = nullptr;
CatDetector * catDetector_ = nullptr;
LedController * ledController_ = nullptr;
FlushButtonController * flushButtonController_ = nullptr;
MQTT_Manager * mqttManager_ = nullptr;
//FlushButtonController * testButtonController_ = nullptr;
//AutoSulivansFeederController * autoSulivansFeederController_ = nullptr;
//AlexaEventSender * alexaEventSender_ = nullptr;

void setupWifi();

void setup(){
    //disableCore0WDT();
    
    Serial.begin(SERIAL_BAUD_RATE);
    Serial.println("Toilet Flusher");

    setupWifi();

    toiletFlusher = new L293dEnstop();
    catDetector_ = new CatDetector();
    ledController_ = new LedController();
    flushButtonController_ = new FlushButtonController(FLUSH_BUTTON_PIN);
    mqttManager_ = new MQTT_Manager(MQTT_SERVER, MQTT_USER, MQTT_PASSWORD);
    //testButtonController_ = new FlushButtonController(BUILTIN_BUTTON_PIN, CAT_DETECTED, NO_EVENT);
    //autoSulivansFeederController_ = new AutoSulivansFeederController();
    //alexaEventSender_ = new AlexaEventSender();

/*
    Event event;
    event.eventType = PRIZE_DELIVERY;
    //event.eventType = FLUSH_BUTTON_PUSHED;
    EventDispatcher::getInstance().sendEvent(event);
    */

}

void setupWifi(){
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
    Serial.println("Connecting to WiFi");
    WiFi.begin(WIFI_SSID, WIFI_PASSWD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    digitalWrite(LED_PIN, HIGH);
    
}

void loop(){
    
    if (WiFi.status() != WL_CONNECTED) {
        ESP.restart();
    }
    esp_task_wdt_reset();  // Si usas ESP-IDF
    vTaskDelay(pdMS_TO_TICKS(200)); // Esperar un poco

}
