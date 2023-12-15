#ifndef DRONE_PICKING_UP_H_
#define DRONE_PICKING_UP_H_

#include "IDroneState.h"
#include "Drone.h"

class DronePickingUp : public IDroneState{
    public:
        DronePickingUp(Drone* drone);
        /**
         * @brief update the drone's state(speed and destination)
         * @param dt Delta time (type: double)
        */
        void update(double dt);
    private:
        Drone* drone;
};

#endif