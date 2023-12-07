#ifndef IDRONE_STATE_H_
#define IDRONE_STATE_H_

#include "Drone.h"

class Drone;

class IDroneState{
    public:

    /**
     * @brief update the car's state(speed and destination)
     * @param dt Delta time (type: double)
    */
    virtual void update(double dt) = 0;

    private:
    Drone* drone;
};

#endif