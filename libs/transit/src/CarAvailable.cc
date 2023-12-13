#include "CarAvailable.h"
#include "CarPickingUp.h"

CarAvailable::CarAvailable(Car* car){
    this->car = car;
    this->car->setColor("white");
}

void CarAvailable::update(double dt){
    if (!this->car->getToNextDestination()){
        this->car->getNextDestination();
    }
    this->car->getToNextDestination()->move(this->car, dt);
    
    // Front of car model faces the wrong way, rotate to compensate
    this->car->rotate(-M_PI / 4 + 0.01);

    if (this->car->getToNextDestination()->isCompleted()) {
        this->car->deleteNextDestination();
        this->car->clearNextDestination();
        this->car->getNextDestination();
    }
    // State changes when car receives notification
}

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
}