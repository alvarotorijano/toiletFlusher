#ifndef AUTOSULIVANS_FEEDER_CONTROLLER_HPP__
#define AUTOSULIVANS_FEEDER_CONTROLLER_HPP__

#include "IFoodDispenser.hpp"

class AutoSulivansFeederController : IFoodDispenser
{
    public:
    AutoSulivansFeederController();
        void dispenseFood();
};

#endif