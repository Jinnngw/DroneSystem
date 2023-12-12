#define _USE_MATH_DEFINES
#include "Drone.h"

#include <cmath>
#include <limits>

#include "AstarStrategy.h"
#include "BeelineStrategy.h"
#include "DfsStrategy.h"
#include "BfsStrategy.h"
#include "DijkstraStrategy.h"
#include "JumpDecorator.h"
#include "SpinDecorator.h"

#include "Package.h"
#include "SimulationModel.h"

#include "DroneAvailable.h"
#include "PackageDataController.h"

Drone::Drone(JsonObject& obj) : IEntity(obj) {
  available = true;
  this->state = new DroneAvailable(this);
}

Drone::~Drone() {
  if (toPackage) delete toPackage;
  if (toFinalDestination) delete toFinalDestination;
  if (state) delete state;
}

void Drone::getNextDelivery() {
  if (model && model->scheduledDeliveries.size() > 0) {
    package = model->scheduledDeliveries.front();
    PackageDataController::getInstance()->addPackage(package);

    if (package) {
      available = false;
      pickedUp = false;

      Vector3 packagePosition = package->getPosition();
      Vector3 finalDestination = package->getDestination();

      // std::cout << "Drone " << packagePosition.x << std::endl;

      toPackage = new BeelineStrategy(position, packagePosition);

      std::string strat = package->getStrategyName();
      if (strat == "astar") {
        toFinalDestination =
          new JumpDecorator(
            new AstarStrategy(
              packagePosition,
              finalDestination,
              model->getGraph()));
      } else if (strat == "dfs") {
        toFinalDestination =
          new SpinDecorator(
            new JumpDecorator(
              new DfsStrategy(
                packagePosition,
                finalDestination,
                model->getGraph())));
      } else if (strat == "bfs") {
        toFinalDestination =
          new SpinDecorator(
            new SpinDecorator(
              new BfsStrategy(
                packagePosition,
                finalDestination,
                model->getGraph())));
      } else if (strat == "dijkstra") {
        toFinalDestination =
          new JumpDecorator(
            new SpinDecorator(
              new DijkstraStrategy(
                packagePosition,
                finalDestination,
                model->getGraph())));
      } else {
        toFinalDestination = new BeelineStrategy(
          packagePosition,
          finalDestination);
      }
    }
  }
}

void Drone::update(double dt) {
  this->state->update(dt);
}

void Drone::changeState(IDroneState* state){
  this->state = state;
}

bool Drone::getAvailable(){
  return this->available;
}

bool Drone::getPickedUp(){
  return this->pickedUp;
}

Package* Drone::getPackage(){
  return this->package;
}

IStrategy* Drone::getToPackage(){
  return this->toPackage;
}

PathStrategy* Drone::getToFinalDestination(){
  return this->toFinalDestination;
}

void Drone::resetToPackage(){
  delete this->toPackage;
  toPackage = nullptr;
}

void Drone::resetPackage(){
  this->package = nullptr;
}

void Drone::resetToFinalDestination(){
  delete toFinalDestination;
  toFinalDestination = nullptr;
}

void Drone::setPickedUp(bool val){
  this->pickedUp = val;
}

void Drone::setAvailable(bool val){
  this->available = val;
}