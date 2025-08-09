#ifndef MQTT_MANAGER_HPP
#define MQTT_MANAGER_HPP

#include "config.h"
#include "EventDispatcher.hpp"
#include <esp_task_wdt.h>

#define DEBUG_MQTT

#ifdef ESP32
  #include <WiFi.h>
#else
  #include <ESP8266WiFi.h>
#endif

#include <PubSubClient.h>

class MQTT_Manager : public Subscriber {
public: 
    MQTT_Manager(const char* server, const char* user, const char* password);
    void MQTTLoop();
    void onEvent(Event event);

private:
    static void callback(char* topic, byte* payload, unsigned int length);
    void reconnect();

    static const char* mqtt_command_topic_toilet;
    static const char* mqtt_state_topic_toilet;
    static const char* mqtt_available_topic_toilet;
    static const char* mqtt_state_topic_catDetector;
    static const char* mqtt_available_topic_catDetector;
    const char* server_;
    const char* user_;
    const char* password_;
    WiFiClient * espClient_;
    PubSubClient * client_;
    // Add any necessary MQTT client library instance here
};

void MQTT_LoopTask(void *pvParameters);

#endif // MQTT_MANAGER_HPP