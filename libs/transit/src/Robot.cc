#include "Robot.h"

Robot::Robot(JsonObject &obj) : IEntity(obj) {}

void Robot::update(double dt) {}

void Robot::receive(Package* p) {
  package = p;
}

void Robot::subscribe(IObserver* observer) {}

void Robot::unsubscribe(IObserver* observer) {}

bool Robot::notifySubscribers(std::string context) { return true;}