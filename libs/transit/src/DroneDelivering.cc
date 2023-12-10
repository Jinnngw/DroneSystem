#include "DroneDelivering.h"
#include "DroneAvailable.h"
#include "Package.h"
#include "IStrategy.h"
#include "PathStrategy.h"

DroneDelivering::DroneDelivering(Drone* drone){
    this->drone = drone;

    // Change Drone attributes to characterize specific state
    this->drone->setColor("red");
    this->drone->setSpeed(30.0);

    // // Change altitude of route to customer
    // PathStrategy* route = static_cast<PathStrategy*>(this->drone->getToFinalDestination());
    // std::cout << "Route found: " << route << std::endl;
    
    // if (route){
    //     std::vector<std::vector<float>> path = route->getPath();
    //     std::cout << "Temporary path variable assigned" << std::endl;
    //     for (int i=0;i<path.size();i++){
    //         path[i][1] += 50;
    //     }
    //     static_cast<PathStrategy*>(this->drone->getToFinalDestination())->setPath(path);
    // }


}

void DroneDelivering::update(double dt){
    // If the drone does not have a package to get to but does still have
    // a final destination to get to from an already picked-up package,
    if (this->drone->getToFinalDestination()) {
        // Move the drone towards the final destination using some IStrategy
        this->drone->getToFinalDestination()->move(this->drone, dt);

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
        }
    }
}