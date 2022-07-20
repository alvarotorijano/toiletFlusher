#ifndef ITOILET_FLUSHER_HPP__
#define ITOILET_FLUSHER_HPP__

#include "EventDispatcher.hpp"

class IToiletFlusher
{
    public: 
        virtual void flush() = 0;
};

#endif