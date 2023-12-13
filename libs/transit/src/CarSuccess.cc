#include "CarSuccess.h"
#include "CarAvailable.h"
#include "SimulationModel.h"
#include "PackageDataController.h"

CarSuccess::CarSuccess(Car* car){
    this->car = car;
}

void CarSuccess::update(double dt){    
    // Remove package from package singleton
    PackageDataController::getInstance()->removePackage(this->car->getPackage());

    // Delete the package from the SimulationModel
        // Two Cars in the Success state may try to delete the same package, so
        // there's a chance one of the Cars tries to remove an already-removed
        // entity from SimulationModel
    SimulationModel* model = this->car->getModel();
    try{
        model->removeFromSim(this->car->getPackage()->getId());
    }
    catch(...){
        std::cout << "Car in Success state tried deleting nonexistent package" << std::endl;
    }

    // Reset package assigned to Car
    this->car->setPackage(nullptr);

    // Decrease speed back to original value
    this->car->setSpeed(30.0);

    // Randomly choose a new destination (getNextDestination)
    this->car->getNextDestination();

    // Change state of car back to Available
    this->car->changeState(new CarAvailable(this->car));

    // Print statement
    std::cout << "Car state changes from success to available" << std::endl;
}

void CarSuccess::notify(Vector3 location, Package* package){

}