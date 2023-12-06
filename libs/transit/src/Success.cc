#include "Success.h"
#include "math/vector3.h"


Success:: updata(double dt){

    //Delete package
    if(this->car->package) delete this->car->package;

    //Randomly choose a new destination (getNextDestination)
    this->car->getNextDestination();


    //Decrease speed back to original value
    this->car->speed = 30.0;

    //Change state back to Available
    this->car->changeState(Available* availableState)

}