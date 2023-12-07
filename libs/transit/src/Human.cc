#define _USE_MATH_DEFINES
#include "Human.h"

#include <cmath>
#include <limits>

#include "AstarStrategy.h"
#include "SimulationModel.h"

#include "IHumanState.h"
#include "HumanLooking.h"

Human::Human(JsonObject& obj) : IEntity(obj) {
  // Initialize the default state
  state = new HumanLooking();
}

Human::~Human() {
  delete state;
  if (movement) delete movement;
}

void Human::update(double dt) { state->update(dt); }

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

std::vector<Package*> Human::getPackages() { return packages.getPackageList(); }

std::vector<ICarSubscriber*> Human::getCars() { return cars; }
