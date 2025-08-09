#include "MQTT_Manager.hpp"

const char* MQTT_Manager::mqtt_command_topic_toilet = "home/toilet/set";
const char* MQTT_Manager::mqtt_state_topic_toilet = "home/toilet/state";
const char* MQTT_Manager::mqtt_available_topic_toilet = "home/toilet/available";
const char* MQTT_Manager::mqtt_state_topic_catDetector = "home/catDetector/state";
const char* MQTT_Manager::mqtt_available_topic_catDetector = "home/catDetector/available";
   

MQTT_Manager::MQTT_Manager(const char* server, const char* user, const char* password) 
    : server_(server), user_(user), password_(password)
{
    espClient_ = new WiFiClient();
    client_ = new PubSubClient(*espClient_);
    
    client_->setServer(server_, 1883);
    client_->setCallback(callback);

    EventDispatcher & eventDispatcher = EventDispatcher::getInstance();
    eventDispatcher.subscribe(eventTypes::CAT_DETECTED, (Subscriber*)this);
    eventDispatcher.subscribe(eventTypes::FLUSH_STARTED, (Subscriber*)this);
    eventDispatcher.subscribe(eventTypes::FLUSH_FINISHED, (Subscriber*)this);

    if (!client_->connected()) {
            reconnect();
        }

    xTaskCreate(
    MQTT_LoopTask,
    "MQTT_task",   // Name of the task (for debugging)
    10000,            // Stack size (bytes)
    this,            // Parameter to pass
    1,               // Task priority
    NULL             // Task handle
    );
}

void MQTT_Manager::callback(char* topic, byte* payload, unsigned int length)
{
    static Event event;
    String message;
    //This could be a memcpy
    for (unsigned int i = 0; i < length; i++) {
        message += (char)payload[i];
    }

    if (String(topic) == mqtt_command_topic_toilet) {
        if (message == "ON") {
            Serial.println("MQTT: Flush command received");
            event.eventType = FLUSH_REQUEST;
            EventDispatcher::getInstance().sendEvent(event);
        }
    }
}

void MQTT_Manager::MQTTLoop(){
    while(1){
        esp_task_wdt_reset();
        if (!client_->connected()) {
            reconnect();
        } else {
            client_->loop();
        }
        delay(1);
    }

}

void MQTT_Manager::onEvent(Event event) {
    if (event.eventType == FLUSH_STARTED) {
        Serial.println("MQTT: Flush started");
        client_->publish(mqtt_state_topic_toilet, "ON", true);
    } else if (event.eventType == FLUSH_FINISHED) {
        Serial.println("MQTT: Flush finished");
        client_->publish(mqtt_state_topic_toilet, "OFF", true);
    } else if (event.eventType == CAT_DETECTED) {
        Serial.println("MQTT: Cat detected");
        client_->publish(mqtt_state_topic_catDetector, "ON", true);
        delay(1000);
        client_->publish(mqtt_state_topic_catDetector, "OFF", true);
    }
}

void MQTT_LoopTask(void *pvParameters){
    MQTT_Manager * controller = (MQTT_Manager *)pvParameters;
    controller->MQTTLoop();
}

void MQTT_Manager::reconnect() {
  while (!client_->connected()) {
#ifdef DEBUG_MQTT
    Serial.print("Attempting MQTT connection...");
#endif
    if (client_->connect("ESP32Switch", "MQTT_AT", "MQTT_AT",
      mqtt_available_topic_toilet,  
       0,                     
      true,                  
      "offline" )) {
      client_->publish(mqtt_available_topic_toilet, "online", true);
      client_->publish(mqtt_available_topic_catDetector, "online", true); 
#ifdef DEBUG_MQTT
      Serial.println("connected");
#endif
      client_->subscribe(mqtt_command_topic_toilet);
#ifdef DEBUG_MQTT
      Serial.print("Subscribed to topic: ");
      Serial.println(mqtt_command_topic_toilet);
#endif
    } else {
#ifdef DEBUG_MQTT
      Serial.print("Failed, rc=");
      Serial.print(client_->state());
      Serial.println(" - retrying in 5 seconds...");
#endif
      vTaskDelay(pdMS_TO_TICKS(2000));
    }
  }
}