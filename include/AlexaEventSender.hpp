#ifndef ALEXA_EVENT_SENDER_HPP
#define ALEXA_EVENT_SENDER_HPP

#define ESPALEXA_ASYNC
#include <Espalexa.h>
#include "config.h"
#include "EventDispatcher.hpp"

#ifdef ARDUINO_ARCH_ESP32
#include <AsyncTCP.h>
#else
#include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>

class AlexaEventSender
{
    private: 
    Espalexa * espalexa;
    AsyncWebServer * server;
    static void flusher(uint8_t dummie);
    static void prizeDelivery(uint8_t dummie);

    public:
    AlexaEventSender();
    ~AlexaEventSender();

    void alexaEventSenderloop();

};

void alexaLoop(void *pvParameters);

#endif
