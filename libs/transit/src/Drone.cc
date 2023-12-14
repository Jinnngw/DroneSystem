#define _USE_MATH_DEFINES
#include "Drone.h"

#include <cmath>
#include <iostream>
#include <limits>

#include "AstarStrategy.h"
#include "BeelineStrategy.h"
#include "BfsStrategy.h"
#include "DfsStrategy.h"
#include "DijkstraStrategy.h"
#include "JumpDecorator.h"
#include "SpinDecorator.h"
#include "Package.h"
#include "SimulationModel.h"

#include "DroneAvailable.h"
#include "PackageDataController.h"

/**
 * @brief Constructor for Drone. Initializes the drone with given JSON data.
 * @param obj JSON object containing initialization data for the drone.
 */
Drone::Drone(JsonObject& obj) : IEntity(obj) {
  available = true;
  this->state = new DroneAvailable(this);
}

/**
 * @brief Destructor for the Drone class. Cleans up resources.
 */
Drone::~Drone() {
  if (toPackage) delete toPackage;
  if (toFinalDestination) delete toFinalDestination;
  if (state) delete state;
}

/**
 * @brief Calculates and assigns the next delivery for the drone.
 */
void Drone::getNextDelivery() {
  
  if (model && model->scheduledDeliveries.size() > 0) {
    package = model->scheduledDeliveries.front();
    PackageDataController::getInstance()->addPackage(package);
    std::cout << "popping front" << std::endl;
    model->scheduledDeliveries.pop_front();
    std::cout << "done popping front" << std::endl;

    if (package) {
      available = false;
      pickedUp = false;

      Vector3 packagePosition = package->getPosition();
      Vector3 finalDestination = package->getDestination();

      // std::cout << "Drone " << packagePosition.x << std::endl;

      toPackage = new BeelineStrategy(position, packagePosition);

      std::string strat = package->getStrategyName();
      if (strat == "astar") {
        toFinalDestination = new JumpDecorator(new AstarStrategy(
            packagePosition, finalDestination, model->getGraph()));
      } else if (strat == "dfs") {
        toFinalDestination =
            new SpinDecorator(new JumpDecorator(new DfsStrategy(
                packagePosition, finalDestination, model->getGraph())));
      } else if (strat == "bfs") {
        toFinalDestination =
            new SpinDecorator(new SpinDecorator(new BfsStrategy(
                packagePosition, finalDestination, model->getGraph())));
      } else if (strat == "dijkstra") {
        toFinalDestination =
            new JumpDecorator(new SpinDecorator(new DijkstraStrategy(
                packagePosition, finalDestination, model->getGraph())));
      } else {
        toFinalDestination =
            new BeelineStrategy(packagePosition, finalDestination);
      }
    }
  }
}

/**
 * @brief Updates the Drone's state.
 * @param dt Time step for the update.
 */
void Drone::update(double dt) {
  this->state->update(dt);
}

/**
 * @brief Changes the state of the Drone.
 * @param state Pointer to the new state object.
 */
void Drone::changeState(IDroneState* state){
  this->state = state;
}

/**
 * @brief Checks whether the drone is available.
 * @return True if the drone is available, false otherwise.
 */
bool Drone::getAvailable(){
  return this->available;
}

/**
 * @brief Checks whether the drone has picked up a package.
 * @return True if the drone has picked up a package, false otherwise.
 */
bool Drone::getPickedUp(){
  return this->pickedUp;
}

/**
 * @brief Retrieves the package currently assigned to the drone.
 * @return Pointer to the assigned Package object.
 */
Package* Drone::getPackage(){
  return this->package;
}

/**
 * @brief Retrieves the strategy to get to the package.
 * @return Pointer to the strategy object for getting to the package.
 */
IStrategy* Drone::getToPackage(){
  return this->toPackage;
}

/**
 * @brief Retrieves the strategy for getting to the final destination.
 * @return Pointer to the PathStrategy object for the final destination.
 */
PathStrategy* Drone::getToFinalDestination(){
  return this->toFinalDestination;
}

/**
 * @brief Resets the strategy to get to the package.
 */
void Drone::resetToPackage(){
  delete this->toPackage;
  toPackage = nullptr;
}

/**
 * @brief Resets the package assigned to the drone.
 */
void Drone::resetPackage(){
  this->package = nullptr;
}

/**
 * @brief Resets the strategy for getting to the final destination.
 */
void Drone::resetToFinalDestination(){
  delete toFinalDestination;
  toFinalDestination = nullptr;
}

/**
 * @brief Sets the status of whether the drone has picked up a package.
 * @param val Boolean value indicating if the package is picked up.
 */
void Drone::setPickedUp(bool val){
  this->pickedUp = val;
}

/**
 * @brief Subscribes an observer to the drone.
 * @param observer Pointer to the IObserver to subscribe.
 */
void Drone::subscribe(IObserver* observer) { observers.push_back(observer); }

/**
 * @brief Unsubscribes an observer from the drone.
 * @param observer Pointer to the IObserver to unsubscribe.
 */
void Drone::unsubscribe(IObserver* observer) {
  observers.erase(std::remove(observers.begin(), observers.end(), observer),
                  observers.end());
}

/**
 * @brief Notifies all subscribers with a specific context.
 * @param context The context of the notification as a string.
 * @return True if there are subscribers and notification was sent, false otherwise.
 */
bool Drone::notifySubscribers(std::string context) {
  if (observers.empty()) {
    std::cout << "No observers found." << std::endl;
    return false;
  }
  for (IObserver* observer : observers) {
    observer->sendNotif(this, context);
  }
  return true;
}

/**
 * @brief Sets the availability status of the drone.
 * @param val Boolean value indicating the availability status of the drone.
 */
void Drone::setAvailable(bool val){
  this->available = val;
}