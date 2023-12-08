#ifndef CAR_SUCCESS_H_
#define CAR_SUCCESS_H_


#include "ICarState.h"

class CarSuccess : public ICarState{

    /**
     * @brief update the car's state(speed and destination)
     * @param dt Delta time (type: double)
    */
    void update(double dt);
};

#endif // CAR_SUCCESS_H_