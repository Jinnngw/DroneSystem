#ifndef DRONE_AVAILABLE_H_
#define DRONE_AVAILABLE_H_

#include "IDroneState.h"
#include "Drone.h"

class DroneAvailable : public IDroneState{
    public:
        DroneAvailable(Drone* drone);

        /**
         * @brief update the car's state(speed and destination)
         * @param dt Delta time (type: double)
        */
        void update(double dt);
    private:
        Drone* drone;
};

#endif