#ifndef IRANGE_METER_HPP__
#define IRANGE_METER_HPP__

class IRangeMeter
{
    public: 
        virtual const float getRangeIn_mm() = 0;
        virtual const float getRangeIn_cm() = 0;
};

#endif