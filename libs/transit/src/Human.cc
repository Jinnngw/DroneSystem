#define _USE_MATH_DEFINES
#include "Human.h"

#include <cmath>
#include <limits>

#include "AstarStrategy.h"
#include "SimulationModel.h"

Human::Human(JsonObject& obj) : IEntity(obj) {}

Human::~Human() {
  if (movement) delete movement;
}

void Human::subscribe(IObserver* observer) {
  // this->observers.push_back(observer);
}

void Human::unsubscribe(IObserver* observer) {
  // this->observers.erase(
  //     std::remove(observers.begin(), observers.end(), observer),
  //     observers.end());
}

bool Human::notifySubscribers() {
  // std::cout << "notification has been called" << std::endl;
  // if (observers.empty()) {
  //   std::cout << "observers is empty" << std::endl;
  //   return false;
  // }

  // for (IObserver* observer : observers) {
  //   std::cout << "observers is not empty" << std::endl;
  //   observer->sendNotif(this);
  //   std::cout << "After sendNotif" << std::endl;
  // }

  return true;
}

void Human::update(double dt) {
  if (movement && !movement->isCompleted()) {
    movement->move(this, dt);
    // notifySubscribers();
  } else {
    // notifySubscribers();
    if (movement) delete movement;
    Vector3 dest;
    dest.x = ((static_cast<double>(rand())) / RAND_MAX) * (2900) - 1400;
    dest.y = position.y;
    dest.z = ((static_cast<double>(rand())) / RAND_MAX) * (1600) - 800;
    if (model) movement = new AstarStrategy(position, dest, model->getGraph());
  }

  // TEMPORARY CODE TO SIMULATE NOTIFICATION SYSTEM, DELETE THIS!!!!
  // this->model->sendNotif(this);
}
