#include "DroneAvailable.h"
#include "DronePickingUp.h"
#include "DroneDelivering.h"
#include "Package.h"
#include "IStrategy.h"
#include "PackageDataController.h"

/**
 * @brief Constructor for DronePickingUp. Initializes the drone's picking-up state.
 * @param drone Pointer to the Drone object.
 */
DronePickingUp::DronePickingUp(Drone* drone){
    this->drone = drone;

    // Change Drone attributes to characterize specific state
    this->drone->setColor("yellow");
    this->drone->setSpeed(25.0);
}

/**
 * @brief Update function for DronePickingUp. Manages the package pickup process.
 * @param dt Time step for the update.
 */
void DronePickingUp::update(double dt){
    // Check if package still exists (may have been stolen)
    bool packageExists = false;
    std::vector<Package*> packages = PackageDataController::getInstance()->getPackageList();
    for (int i=0;i<packages.size();i++){
        if (packages.at(i) == this->drone->getPackage()){
            packageExists = true;
        }
    }

    // If drone has a package to get to,
    if (this->drone->getToPackage() && packageExists) {
        // Move the drone some distance towards the package location
        this->drone->getToPackage()->move(this->drone, dt);

        // If the drone has reached the package location,
        if (this->drone->getToPackage()->isCompleted()) {

            // Clear the package location and set the package as being picked up
            this->drone->resetToPackage();
            this->drone->setPickedUp(true);            

            // Remove the package from the Package singleton
            PackageDataController::getInstance()->removePackage(this->drone->getPackage());

            // Change the Drone's state to Delivering
            this->drone->changeState(new DroneDelivering(this->drone));

            // Terminal output for easier debugging
            std::cout << "Drone has been set from PickingUp to Delivering" << std::endl;

            // Package has been picked up, notify SimulationModel (the observer)
            this->drone->setDetails("dest", this->drone->getPackage()->getName());
            this->drone->notifySubscribers("PackagePickedUp");
        }
    }
    // Otherwise, package has been stolen, change state to Available
    else{
        // Reset package assigned to Drone
        this->drone->resetToPackage();

        // Change state of Drone from PickingUp to Available
        this->drone->changeState(new DroneAvailable(this->drone));
        std::cout << "Drone set from PickingUp to Available (package no longer exists)" << std::endl;
    }
}