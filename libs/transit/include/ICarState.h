#ifndef ICAR_STATE_H_
#define ICAR_STATE_H_

#include "Car.h"
#include "math/vector3.h"
#include "Package.h"

class Car;

class ICarState{
    public:

    /**
     * @brief update the car's state(speed and destination)
     * @param dt Delta time (type: double)
    */
    virtual void update(double dt) = 0;
    virtual void notify(Vector3 location, Package* package) = 0;

    protected:
    Car* car;
};

#endif