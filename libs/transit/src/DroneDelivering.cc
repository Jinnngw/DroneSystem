#include "DroneDelivering.h"
#include "DroneAvailable.h"
#include "Package.h"
#include "IStrategy.h"
#include "PathStrategy.h"

DroneDelivering::DroneDelivering(Drone* drone){
    this->drone = drone;

    // Change Drone attributes to characterize specific state
    this->drone->setColor("red");
    this->drone->setSpeed(35.0);

}

void DroneDelivering::update(double dt){
    // If the drone does not have a package to get to but does still have
    // a final destination to get to from an already picked-up package,
    if (this->drone->getToFinalDestination()) {    
        // std::cout << "before move in delivering" << std::endl;

        // Move the drone towards the final destination using some IStrategy
        this->drone->getToFinalDestination()->move(this->drone, dt);
            
        // std::cout << "after move in delivering" << std::endl;

        // If the drone has a package and it has picked it up,
        if (this->drone->getPackage() && this->drone->getPickedUp()) {
            // Update the position and direction of the package to match the drone
            this->drone->getPackage()->setPosition(this->drone->getPosition());
            this->drone->getPackage()->setDirection(this->drone->getDirection());
        }

        // If the drone has reached the final destination of the package,
        if (this->drone->getToFinalDestination()->isCompleted()) {
            // Reset the drone's final destination
            this->drone->resetToFinalDestination();

            // Saving package name before it is released
            std::string destination = this->drone->getPackage()->getName();

            // Handoff the package to the customer
            this->drone->getPackage()->handOff();

            // Reset the package assigned to the drone
            this->drone->resetPackage();

            // Drone is available again and does not have a package picked up
            this->drone->setAvailable(true);            
            this->drone->setPickedUp(false);

            // Set Drone's state to Available
            this->drone->changeState(new DroneAvailable(this->drone));

            // Terminal output for easier debugging
            std::cout << "Drone has been set from Delivering to Available" << std::endl;

            // Package has been delivered, notify SimulationModel
            this->drone->setDetails("dest", destination);
            this->drone->notifySubscribers("DeliveryCompleted");
        }
    }
}