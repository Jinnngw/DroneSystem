#include "PickingUp.h"

PickingUp:: updata(double dt){

// Update toNextDestination (Take the location of the package notified by the Human as the next destination)

// Increase speed
this->car->speed = 50.0;

// When at toNextDesination (i.e. Package location), change state to Success
if (this->car->toNextDestination->isCompleted()) {
    delete this->car->toNextDestination;
    this->car->toNextDestination = nullptr;
    this->car->changeState(Success* success);
  }
  
}