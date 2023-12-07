#ifndef DRONE_DELIVERING_H_
#define DRONE_DELIVERING_H_

#include "IDroneState.h"

class DroneDelivering: public IDroneState{

    /**
     * @brief update the car's state(speed and destination)
     * @param dt Delta time (type: double)
    */
    void update(double dt);
};

#endif