#ifndef SUCCESS_H_
#define SUCCESS_H_

#include "ICarState.h"

class Success : public ICarState{

/**
     * @brief update the car's state(speed and destination)
     * @param dt Delta time (type: double)
    */
    void update(double dt);
    
};

#endif