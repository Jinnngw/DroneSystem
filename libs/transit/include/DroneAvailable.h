#ifndef DRONE_AVAILABLE_H_
#define DRONE_AVAILABLE_H_

#include "IDroneState.h"

class DroneAvailable : public IDroneState{

    /**
     * @brief update the car's state(speed and destination)
     * @param dt Delta time (type: double)
    */
    virtual void update(double dt) = 0;
};

#endif