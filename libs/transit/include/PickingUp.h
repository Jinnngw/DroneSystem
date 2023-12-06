#ifndef PICKING_UP_H_
#define PICKING_UP_H_

#include "ICarState.h"

class PickingUp : public ICarState{

    /**
     * @brief update the car's state(speed and destination)
     * @param dt Delta time (type: double)
    */
    void update(double dt);
};

#endif