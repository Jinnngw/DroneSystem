/**
 * @file CarPickingUp.cc
 * @brief Implementation of the CarPickingUp state class.
 */

#include "CarPickingUp.h"
#include "CarSuccess.h"
#include "CarAvailable.h"
#include "PackageDataController.h"

/**
 * @brief Constructor for CarPickingUp state.
 * @param car Pointer to the Car associated with this state.
 */
CarPickingUp::CarPickingUp(Car* car){
    this->car = car;
    this->car->setColor("red");

    // Increase speed
    this->car->setSpeed(this->car->getSpeed() + 20.0);
}

/**
 * @brief Updates the state of the Car when it's picking up a package.
 * @param dt Time step for the update.
 */
void CarPickingUp::update(double dt){
    // Check if package still exists (may have already been stolen by another car)
    bool packageExists = false;
    std::vector<Package*> packages = PackageDataController::getInstance()->getPackageList();
    for (int i=0;i<packages.size();i++){
        if (packages.at(i) == this->car->getPackage()){
            packageExists = true;
        }
    }

    // When at toNextDesination (i.e. Package location), change state to Success
    if (this->car->getToNextDestination()->isCompleted() && packageExists) {
        this->car->deleteNextDestination();
        this->car->clearNextDestination();

        // std::cout << "Car has get to package's destination" << std::endl;

        this->car->changeState(new CarSuccess(this->car));
        std::cout << "Car state changes from pickingup to success" << std::endl;

        // Notifying observer (SimulationModel) that car has stolen package
        this->car->setDetails("package", this->car->getPackage()->getName());
        this->car->notifySubscribers("StolePackage");
    }
    // Otherwise, if package still exists then not yet at package location, continue driving towards it
    else if (packageExists){
        this->car->getToNextDestination()->move(this->car, dt);
        
        // Front of car model faces the wrong way, rotate to compensate
        this->car->rotate(-M_PI / 4 + 0.01);
        
        // std::cout << this->car->getName() << " distance to package is " << this->car->getPosition().dist(this->car->getPackage()->getPosition()) << std::endl;
    }
    // Otherwise, package has already been stolen and destroyed by another car, change state back to Available
    else{        
        // Changing car state from PickingUp to Available
        this->car->changeState(new CarAvailable(this->car));
        this->car->setSpeed(this->car->getSpeed() - 20.0);
    }
}

/**
 * @brief Handle notifications received by the Car in the PickingUp state.
 * @param location Location of the package.
 * @param package Pointer to the package.
 */
void CarPickingUp::notify(Vector3 location, Package* package){

}