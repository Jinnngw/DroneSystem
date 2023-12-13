#include "CarAvailable.h"

CarAvailable::CarAvailable(Car* car){
    this->car = car;
    this->car->setColor("white");

    std::cout << "Car set to white (available)" << std::endl;
}

void CarAvailable::update(double dt){
    std::cout << "CARAVAILABLE 1" << std::endl;
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
    std::cout << "CARAVAILABLE 2" << std::endl;
}