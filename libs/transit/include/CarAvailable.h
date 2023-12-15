#ifndef CAR_AVAILABLE_H_
#define CAR_AVAILABLE_H_

#include "ICarState.h"
#include "Car.h"

/**
 * @class CarAvailable
 * @brief Represents the 'Available' state of a Car in the simulation.
 */
class CarAvailable : public ICarState{
    public:
        CarAvailable(Car* car);
        /**
         * @brief update the car's state(speed and destination)
         * @param dt Delta time (type: double)
        */
        void update(double dt);
        /**
        * @brief Handles notifications received by the Car.
        * @param location The location to which the notification pertains (type: Vector3).
        * @param package Pointer to the Package involved in the notification.
        */
        void notify(Vector3 location, Package* package);
};

#endif