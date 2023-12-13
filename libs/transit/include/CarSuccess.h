#ifndef CAR_SUCCESS_H_
#define CAR_SUCCESS_H_


#include "ICarState.h"
#include "Car.h"

class CarSuccess : public ICarState{
    public:
        CarSuccess(Car* car);

        /**
         * @brief update the car's state(speed and destination)
         * @param dt Delta time (type: double)
        */
        void update(double dt);
        void notify(Vector3 location, Package* package);
};

#endif // CAR_SUCCESS_H_