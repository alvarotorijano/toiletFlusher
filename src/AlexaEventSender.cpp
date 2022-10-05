#include "AlexaEventSender.hpp"

AlexaEventSender::AlexaEventSender()
{

    espalexa = new Espalexa();
    server = new AsyncWebServer(80);

/*
    if (espalexa == nullptr || server == nullptr)
    {
        Serial.println("Failed to allocate memory for AlexaEventSender: rebooting");
        ESP.restart();
    }
    */

    server->on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(200, "text/plain", "This is an example index page your server may send.");
    });
    server->on("/test", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(200, "text/plain", "This is a second subpage you may have.");
    });
    server->onNotFound([this](AsyncWebServerRequest *request){
      if (!espalexa->handleAlexaApiCall(request)) //if you don't know the URI, ask espalexa whether it is an Alexa control request
      {
        //whatever you want to do with 404s
        request->send(404, "text/plain", "Not found");
      }
    });

    espalexa->addDevice(ALEXA_FLUSHER_SPOKEN_NAME, flusher); //simplest definition, default state off
    espalexa->addDevice(ALEXA_PRIZE_DEVILER_SPOKEN_NAME, prizeDelivery); //simplest definition, default state off

    espalexa->begin(server);

    xTaskCreate(
    alexaLoop,
    "alexa_task",   // Name of the task (for debugging)
    10000,            // Stack size (bytes)
    this,            // Parameter to pass
    1,               // Task priority
    NULL             // Task handle
    );
    
}

void AlexaEventSender::prizeDelivery(uint8_t dummie){
    static Event event;
    event.eventType = ALEXA_PRIZE_DELIVERY;
    Serial.println("Event ALEXA_PRIZE_DELIVERY");
    EventDispatcher::getInstance().sendEvent(event);
}

void AlexaEventSender::flusher(uint8_t dummie){
    static Event event;
    event.eventType = ALEXA_FLUSH;
    Serial.println("Event ALEXA_FLUSH");
    EventDispatcher::getInstance().sendEvent(event);
}
void AlexaEventSender::alexaEventSenderloop(){
    while(1){
        espalexa->loop();
        delay(1);
    }

}

void alexaLoop(void *pvParameters){
    AlexaEventSender * controller = (AlexaEventSender *)pvParameters;
   controller->alexaEventSenderloop();
}