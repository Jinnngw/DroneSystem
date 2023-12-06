#define _USE_MATH_DEFINES
#include "Human.h"

#include <cmath>
#include <limits>

#include "AstarStrategy.h"
#include "SimulationModel.h"

Human::Human(JsonObject& obj) : IEntity(obj) {
  // Initialize the default state
  state = new LookingState(this);
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

std::vector<Package*> Human::getPackages() { return packages.getPackageList(); }

std::vector<ICarSubscriber*> Human::getCars() { return cars; }
