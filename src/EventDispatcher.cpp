#include <EventDispatcher.hpp>

#include <Arduino.h>

EventDispatcher &EventDispatcher::getInstance()
{
    static EventDispatcher instance;
    return instance;
}

void EventDispatcher::subscribe(eventType_t eventType, Subscriber * sub)
{
    if(subscribers.find(eventType)==subscribers.end()){
        subscribers.insert(std::pair<eventType_t, std::set<Subscriber*>>(eventType, std::set<Subscriber*>()));
        //subscribers[eventType] = std::set<Subscriber*>();
    }
    subscribers[eventType].insert(sub);
    //Serial.println("Event: " + String(eventType) + "Subs: " + String(subscribers[eventType].size()));
}

void EventDispatcher::unsubscribe(eventType_t eventType, Subscriber * sub)
{
    if(subscribers.find(eventType)!=subscribers.end()){
        subscribers[eventType].erase(sub);
    }
}

void EventDispatcher::sendEvent(Event event)
{
    //Serial.println("Event: " + event.eventType);
    //Serial.println("Elements in vector: " + subscribers[event.eventType].size());
    if(subscribers.find(event.eventType)!=subscribers.end()){
        for(auto sub : subscribers[event.eventType]){
            sub->onEvent(event);
        }
    }
}