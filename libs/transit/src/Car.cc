/**
 * @file Car.cc
 * @brief Implementation of the Car class, representing a car in the simulation.
 */

#include "Car.h"

#include <cmath>
#include <ctime>
#include "DijkstraStrategy.h"
#include "SimulationModel.h"
#include "ICarState.h"
#include "CarPickingUp.h"
#include "CarAvailable.h"
#include "Package.h"
#include "Human.h"


/**
 * @brief Constructor for Car.
 * @param obj JSON object containing initialization data.
 */
Car::Car(JsonObject& obj) : IEntity(obj) {
  std::srand(static_cast<unsigned int>(std::time(0)));
  this->state = new CarAvailable(this);
}

/**
 * @brief Destructor for the Car class.
 */
Car::~Car() {
  if (toNextDestination) delete toNextDestination;
}

// WARNING: big difference between getToNextDestination and getNextDestination
  // getToNextDestination will just return the current toNextDestination
  // getNextDestination will get a BRAND NEW destination and set the DijkstraStrategy accordingly

/**
 * @brief Retrieves the current destination strategy.
 * @return Pointer to the current destination strategy object.
 */
IStrategy* Car::getToNextDestination(){
  return this->toNextDestination;
}

/**
 * @brief Calculates and sets a new random destination for the Car.
 */
void Car::getNextDestination() {
  if (model) {
    // Generate random destination using rand()
    double x = (std::rand() % static_cast<int>(maxX - minX + 1)) + minX;
    double y = (std::rand() % static_cast<int>(maxY - minY + 1)) + minY;
    double z = (std::rand() % static_cast<int>(maxZ - minZ + 1)) + minZ;

    destination = Vector3(x, y, z);

    this->toNextDestination =
        new DijkstraStrategy(position, destination, model->getGraph());
  }
}

/**
 * @brief Sets the next destination for the Car.
 * @param dest The next destination as a Vector3.
 */
void Car::setNextDestination(Vector3 dest){
  toNextDestination = new DijkstraStrategy(position, dest, model->getGraph());
}

/**
 * @brief Clears the current destination strategy.
 */
void Car::clearNextDestination(){
  toNextDestination = nullptr;
}

/**
 * @brief Deletes the current destination strategy object.
 */
void Car::deleteNextDestination(){
  delete this->toNextDestination;
}

/**
 * @brief Retrieves the package currently assigned to the Car.
 * @return Pointer to the assigned Package.
 */
Package* Car::getPackage(){
  return this->package;
}

/**
 * @brief Assigns a package to the Car.
 * @param package Pointer to the Package to assign.
 */
void Car::setPackage(Package* package){
  this->package = package;
}

/**
 * @brief Updates the Car's state.
 * @param dt Time step for the update.
 */
void Car::update(double dt) {
  this->state->update(dt);
}

/**
 * @brief Changes the state of the Car.
 * @param state Pointer to the new state object.
 */
void Car::changeState(ICarState* state) {
  this->state = state;
}

/**
 * @brief Notifies the Car about a package's location.
 * @param location The location of the package.
 * @param package Pointer to the package.
 */
void Car::notify(Vector3 location, Package* package){
  std::cout << "NOTIFY IN CAR" << std::endl;
  this->state->notify(location, package);
}