#include "Car.h"

#include <cmath>
#include <ctime>

#include "DijkstraStrategy.h"
#include "SimulationModel.h"
#include "ICarState.h"
#include "Available.h"
#include "PickingUp.h"
#include "Success.h"

Car::Car(JsonObject& obj,Available* availableState) : IEntity(obj) {
  std::srand(static_cast<unsigned int>(std::time(0)));
  this->state = availableState;
}

Car::~Car() {
  if (toNextDestination) delete toNextDestination;
}

void Car::getNextDestination() {
  if (model) {
    // Generate random destination using rand()
    double x = (std::rand() % static_cast<int>(maxX - minX + 1)) + minX;
    double y = (std::rand() % static_cast<int>(maxY - minY + 1)) + minY;
    double z = (std::rand() % static_cast<int>(maxZ - minZ + 1)) + minZ;

    destination = Vector3(x, y, z);

    toNextDestination =
        new DijkstraStrategy(position, destination, model->getGraph());
  }
}

void Car::update(double dt) {

  this->state->update(dt);

  if (!toNextDestination) {
    getNextDestination();
  }
  toNextDestination->move(this, dt);

  // Front of car model faces the wrong way, rotate to compensate
  this->rotate(-M_PI / 4 + 0.01);

  if (toNextDestination->isCompleted()) {
    delete toNextDestination;
    toNextDestination = nullptr;
    getNextDestination();
  }

}



void Car::changeState(ICarState* state) {
  this->state = state;
}
