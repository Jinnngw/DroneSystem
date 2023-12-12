#include "CarPickingUp.h"
#include "CarSuccess.h"
#include "CarAvailable.h"

void CarPickingUp::update(double dt){
    // Assign Package to Car
    // this->car->setPackage();

    // Update toNextDestination (Take the location of the package notified by the Human as the next destination)
    // Have set the destination in Car's notify()
    // this->car->setNextDestination(this->car->getPackage()->getPosition());

    // Increase speed
    this->car->setSpeed(this->car->getSpeed() + 50.0);

    // When at toNextDesination (i.e. Package location), change state to Success
    if (this->car->getToNextDestination()->isCompleted()) {
        this->car->deleteNextDestination();
        this->car->clearNextDestination();
        this->car->changeState(new CarSuccess());

        std::cout << "Car has get to package's destination" << std::endl;
        std::cout << "Car' state changes from pickingup to success" << std::endl;
    }

    else{
        this->car->getNextDestination();  
    }
}