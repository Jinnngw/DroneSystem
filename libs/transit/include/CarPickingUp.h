#ifndef CAR_PICKING_UP_H_
#define CAR_PICKING_UP_H_

#include "ICarState.h"
#include "Car.h"

/**
 * @class CarPickingUp
 * @brief Represents the 'Picking Up' state of a Car in the simulation.
 *
 * This state is active when the Car is en route to pick up a package. It defines
 * the specific behaviors and actions of a Car when it is engaged in moving towards
 * a package's location for interception.
 */
class CarPickingUp : public ICarState{
    public:
        CarPickingUp(Car* car);
        /**
         * @brief update the car's state(speed and destination)
         * @param dt Delta time (type: double)
        */
        void update(double dt);
        /**
        * @brief Handles notifications received by the Car in the 'Picking Up' state.
        * @param location The updated location relevant to the Car (type: Vector3).
        * @param package Pointer to the Package involved in the notification.
        */
        void notify(Vector3 location, Package* package);
};

#endif