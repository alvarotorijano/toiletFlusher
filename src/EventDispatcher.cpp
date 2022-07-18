#include <EventDispatcher.hpp>

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
}

void EventDispatcher::unsubscribe(eventType_t eventType, Subscriber * sub)
{
    if(subscribers.find(eventType)!=subscribers.end()){
        subscribers[eventType].erase(sub);
    }
}

void EventDispatcher::sendEvent(Event event)
{
    if(subscribers.find(event.eventType)!=subscribers.end()){
        for(auto sub : subscribers[event.eventType]){
            sub->onEvent(event);
        }
    }
}