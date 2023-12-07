#ifndef CAR_PICKING_UP_H_
#define CAR_PICKING_UP_H_

#include "ICarState.h"

class CarPickingUp : public ICarState{

    /**
     * @brief update the car's state(speed and destination)
     * @param dt Delta time (type: double)
    */
    void update(double dt);
};

#endif