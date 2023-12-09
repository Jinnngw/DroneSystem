#include "CarAvailable.h"

CarAvailable::CarAvailable(Car* car){
    this->car = car;
}

void CarAvailable::update(double dt){
    if (!this->car->getToNextDestination()) {
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
}

// Notify function here when implmementing notifications from Humans