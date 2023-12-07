#ifndef DRONE_PICKING_UP_H_
#define DRONE_PICKING_UP_H_

#include "IDroneState.h"

class DronePickingUp : public IDroneState{

    /**
     * @brief update the drone's state(speed and destination)
     * @param dt Delta time (type: double)
    */
    void update(double dt);
};

#endif