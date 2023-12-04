#include "Car.h"

#include <cmath>
#include <ctime>

#include "DijkstraStrategy.h"
#include "SimulationModel.h"

Car::Car(JsonObject& obj) : IEntity(obj) {
  std::srand(static_cast<unsigned int>(std::time(0)));
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
  if (!toNextDestination) {
    getNextDestination();
  }
  toNextDestination->move(this, dt);

  // Front of car model faces the wrong way, rotate to compensate
  this->rotate(-M_PI / 4 + 0.01);

  if (toNextDestination->isCompleted()) {
    notifySubscribers("ReachedDestination");
    delete toNextDestination;
    toNextDestination = nullptr;
    getNextDestination();
    notifySubscribers("NewDestination");
  }
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
