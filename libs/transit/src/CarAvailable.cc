/**
 * @file CarAvailable.cc
 * @brief Implementation of the CarAvailable state class, representing an available state of the Car.
 */

#include "CarAvailable.h"
#include "CarPickingUp.h"

/**
 * @brief Constructor for the CarAvailable state.
 * @param car Pointer to the Car associated with this state.
 */
CarAvailable::CarAvailable(Car* car){
    this->car = car;
    this->car->setColor("white");
}

/**
 * @brief Updates the CarAvailable state.
 * @param dt Time step for the update.
 */
void CarAvailable::update(double dt){
    // Giving Car it's initial destination (occurs once)
    if (!this->car->getToNextDestination()){
        this->car->getNextDestination();

        // Notifying observer (SimulationModel) that car is driving to new destination
        this->car->setDetails("dest", this->car->getDestinationCoords().toString());
        this->car->notifySubscribers("NewDestination");
    }
    this->car->getToNextDestination()->move(this->car, dt);
    
    // Front of car model faces the wrong way, rotate to compensate
    this->car->rotate(-M_PI / 4 + 0.01);

    if (this->car->getToNextDestination()->isCompleted()) {
        this->car->deleteNextDestination();
        this->car->clearNextDestination();
        this->car->getNextDestination();

        // Notifying observer (SimulationModel) that car is driving to new destination
        this->car->setDetails("dest", this->car->getDestinationCoords().toString());
        this->car->notifySubscribers("NewDestination");
    }
}

/**
 * @brief Notifies the CarAvailable state about a package's location.
 * @param location The location of the package.
 * @param package Pointer to the package.
 */
void CarAvailable::notify(Vector3 location, Package* package){

    // std::cout << "car receives the package's location" << std::endl;

    //set the car's next destination to package's location
    this->car->setNextDestination(location);

    //set the car's package pointer pointes to the new package.
    this->car->setPackage(package);

    //change the car's state from available to picking up
    this->car->changeState(new CarPickingUp(this->car));
    std::cout << "Car's state has changed from Available to PickingUp" << std::endl;
    // std::cout << "Package pointer assigned to car is " << this->package << std::endl;
    
    // Notifying observer (SimulationModel) that human is notifying cars to steal package
    this->car->setDetails("package", this->car->getPackage()->getName());
    this->car->notifySubscribers("TryingToStealPackage");
}