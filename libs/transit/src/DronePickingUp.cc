#include "DronePickingUp.h"
#include "DroneDelivering.h"
#include "Package.h"
#include "IStrategy.h"
#include "PackageDataController.h"


DronePickingUp::DronePickingUp(Drone* drone){
    this->drone = drone;

    // Change Drone attributes to characterize specific state
    this->drone->setColor("yellow");
    this->drone->setSpeed(15.0);
}

void DronePickingUp::update(double dt){
    // If there is a package to get to,
    if (this->drone->getToPackage()) {
        // Move the drone some distance towards the package location
        this->drone->getToPackage()->move(this->drone, dt);
        
        // If the drone has reached the package location,
        if (this->drone->getToPackage()->isCompleted()) {
            // Clear the package location and set the package as being picked up
            this->drone->resetToPackage();
            this->drone->setPickedUp(true);

            // Remove the package from the Package singleton AND the scheduled deliveries stack
            PackageDataController::getInstance()->removePackage(this->drone->getPackage());
            this->drone->getModel()->scheduledDeliveries.pop_front();

            // Change the Drone's state to Delivering
            this->drone->changeState(new DroneDelivering(this->drone));

            // Terminal output for easier debugging
            std::cout << "Drone has been set from PickingUp to Delivering" << std::endl;
        }
    }
}