#include "Car.h"

#include <cmath>
#include <ctime>

#include "DijkstraStrategy.h"
#include "SimulationModel.h"

Car::Car(JsonObject& obj) : IEntity(obj) {
  std::srand(static_cast<unsigned int>(std::time(0)));
}

Car::~Car() {
  if (movement) delete movement;
}

void Car::subscribe(IObserver* observer) {
  this->observers.push_back(observer);
}

void Car::unsubscribe(IObserver* observer) {
  this->observers.erase(
      std::remove(observers.begin(), observers.end(), observer),
      observers.end());
}

bool Car::notifySubscribers(std::string context) {
  // std::cout << "notification has been called" << std::endl;
  if (observers.empty()) {
    std::cout << "No observers found" << std::endl;
    return false;
  }

  for (IObserver* observer : observers) {
    // std::cout << "observers is not empty" << std::endl;
    observer->sendNotif(this, context);
    // std::cout << "sendNotif completed" << std::endl;
  }

  return true;
}

void Car::update(double dt) {
  if (movement && !movement->isCompleted()) {
    movement->move(this, dt);
    // Front of car model faces the wrong way, rotate to compensate
    this->rotate(-M_PI / 4 + 0.01);
  } else {
    if (movement) delete movement;
    Vector3 dest;
    dest.x = ((static_cast<double>(rand())) / RAND_MAX) * (2900) - 1400;
    dest.y = position.y;
    dest.z = ((static_cast<double>(rand())) / RAND_MAX) * (1600) - 800;
    if (model)
      movement = new DijkstraStrategy(position, dest, model->getGraph());
    
    // Notifying observer (SimulationModel) that car is driving to new destination
    this->setDetails("dest", dest.toString());
    notifySubscribers("NewDestination");
  }
}
