#include "CarPickingUp.h"
#include "CarSuccess.h"
#include "CarAvailable.h"
#include "PackageDataController.h"

CarPickingUp::CarPickingUp(Car* car){
    this->car = car;
    this->car->setColor("red");

    // Increase speed
    this->car->setSpeed(this->car->getSpeed() + 20.0);
}

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

        std::cout << "Car has get to package's destination" << std::endl;

        this->car->changeState(new CarSuccess(this->car));
        std::cout << "Car state changes from pickingup to success" << std::endl;
    }
    // Otherwise, if package still exists then not yet at package location, continue driving towards it
    else if (packageExists){
        this->car->getToNextDestination()->move(this->car, dt);
        // std::cout << this->car->getName() << " distance to package is " << this->car->getPosition().dist(this->car->getPackage()->getPosition()) << std::endl;
    }
    // Otherwise, package has already been stolen and destroyed by another car, change state back to Available
    else{
        this->car->changeState(new CarAvailable(this->car));
        this->car->setSpeed(this->car->getSpeed() - 20.0);
    }
}