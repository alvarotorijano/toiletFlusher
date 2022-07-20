#ifndef EVENT_DISPATCHER_HPP__
#define EVENT_DISPATCHER_HPP__

#include <map>
#include <set>
#include <memory>

enum eventTypes{
    NO_EVENT,
    CAT_DETECTED,
    CAT_NOT_DETECTED,
    FLUSH_BUTTON_PUSHED,
    FLUSH_BUTTON_RELEASED,
    FLUSH_STARTED,
    FLUSH_FINISHED
};

typedef enum eventTypes eventType_t;

class Event {
    public:
        eventType_t eventType = NO_EVENT;
        std::shared_ptr<void> eventData = nullptr;
};

class Subscriber {
    public:
        virtual void onEvent(Event event) = 0;
};

class EventDispatcher {

    public:
        static EventDispatcher &getInstance();
        void sendEvent(Event event);
        void subscribe(eventType_t eventType, Subscriber * sub);
        void unsubscribe(eventType_t eventType, Subscriber * sub);



    private:
        EventDispatcher(){};
        //EventDispatcher(EventDispatcher const &);
        //void operator=(EventDispatcher const &);
        
        std::map<eventType_t, std::set<Subscriber*>> subscribers;

    public:
        EventDispatcher(EventDispatcher const &) = delete;
        void operator=(EventDispatcher const &) = delete;

};

#endif