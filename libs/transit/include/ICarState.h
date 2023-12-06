#ifndef ICAR_STATE_H_
#define ICAR_STATE_H_

#include "Car.h"

class Car;

class ICarState{
    public:

    /**
     * @brief update the car's state(speed and destination)
     * @param dt Delta time (type: double)
    */
    virtual void update(double dt) = 0;

    private:
    Car* car;
};

#endif