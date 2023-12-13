/**
 * @file CarSuccess.cc
 * @brief Implementation of the CarSuccess state class.
 */

#include "CarSuccess.h"
#include "CarAvailable.h"
#include "SimulationModel.h"
#include "PackageDataController.h"

/**
 * @brief Constructor for CarSuccess state.
 * @param car Pointer to the Car associated with this state.
 */
CarSuccess::CarSuccess(Car* car){
    this->car = car;
}

/**
 * @brief Updates the state of the Car after successful package delivery.
 * @param dt Time step for the update.
 */
void CarSuccess::update(double dt){    
    // Remove package from package singleton
    PackageDataController::getInstance()->removePackage(this->car->getPackage());

    // Delete the package from the SimulationModel
    SimulationModel* model = this->car->getModel();
    model->removeFromSim(this->car->getPackage()->getId());

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

/**
 * @brief Handle notifications received by the Car in the Success state.
 * @param location Location of the package.
 * @param package Pointer to the package.
 */
void CarSuccess::notify(Vector3 location, Package* package){

}