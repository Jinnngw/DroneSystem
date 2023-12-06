#ifndef AVAILABLE_H_
#define AVAILABLE_H_

#include "ICarState.h"

class Available : public ICarState{
   
    /**
     * @brief update the car's state(speed and destination)
     * @param dt Delta time (type: double)
    */
    void update(double dt);
};

#endif