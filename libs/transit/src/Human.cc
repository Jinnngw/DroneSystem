#define _USE_MATH_DEFINES
#include "Human.h"

#include <cmath>
#include <limits>

#include "AstarStrategy.h"
#include "SimulationModel.h"

#include "IHumanState.h"
#include "HumanLooking.h"
#include "HumanAvailable.h"
#include "Package.h"


Human::Human(JsonObject& obj) : IEntity(obj) {
  this->packages = PackageDataController::getInstance();
  // Initialize the default state
  state = new HumanAvailable(this);
}

Human::~Human() {
  delete state;
  if (movement) delete movement;
}

void Human::update(double dt) {
  state->update(dt);
}

void Human::changeState(IHumanState* newState) {
  delete state;
  state = newState;
}

IStrategy* Human::getMovement(){
  return this->movement;
}

void Human::setMovement(IStrategy* movement){
  this->movement = movement;
}

void Human::deleteMovement(){
  delete movement;
}

Package* Human::getPackage() {return package;}

SimulationModel* Human::getModel() {return model;}

std::vector<Package*> Human::getPackages() { return packages->getPackageList(); }

std::vector<ICarSubscriber*> Human::getCars() { return cars; }
