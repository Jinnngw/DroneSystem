#ifndef DRONE_DELIVERING_H_
#define DRONE_DELIVERING_H_

#include "IDroneState.h"
#include "Drone.h"

class DroneDelivering: public IDroneState{
    public:
        DroneDelivering(Drone* drone);

        /**
         * @brief update the car's state(speed and destination)
         * @param dt Delta time (type: double)
        */
        void update(double dt);
    private:
        Drone* drone;
};

#endif