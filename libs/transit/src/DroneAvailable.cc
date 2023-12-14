#include "DroneAvailable.h"
#include "DronePickingUp.h"
#include "Package.h"
#include "IStrategy.h"

/**
 * @brief Constructor for DroneAvailable. Sets the initial state of the drone.
 * @param drone Pointer to the Drone object being controlled.
 */
DroneAvailable::DroneAvailable(Drone* drone){
    this->drone = drone;

    // Change Drone attributes to characterize specific state
    this->drone->setColor("green");
    this->drone->setSpeed(0.0);

}

/**
 * @brief Update function for DroneAvailable. Manages the state transitions and actions when the drone is available.
 * @param dt The time step for the update.
 */
void DroneAvailable::update(double dt){
    // std::cout << "Update for available state of drone" << std::endl;

    // If the drone is available,
    if (this-drone->getAvailable()){
        // then see if there is a new delivery and, if so, assign it to the Drone
        this->drone->getNextDelivery();
    }

    // If there is a package to get to,
    if (this->drone->getToPackage()) {
        // then change the Drone's state to PickingUp
        this->drone->changeState(new DronePickingUp(this->drone));

        // Terminal output for easier debugging
        std::cout << "Drone has been set from Available to PickingUp" << std::endl;

        // Assign the package's name as the dest value in details of Drone
        this->drone->setDetails("dest", this->drone->getPackage()->getName());
        
        // Notify SimulationModel
        this->drone->notifySubscribers("StartedDelivery");
    }
}