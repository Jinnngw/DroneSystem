#include "HumanFound.h"

#include "AstarStrategy.h"
#include "JumpDecorator.h"

void HumanFound::update(double dt) {
  Package* closestPackage = findClosestPackage();

  if (closestPackage) {
    moveTowardsPackage();
  } else {
    // No package found, revert to Looking state
    human->changeState(new HumanLooking());
  }
}

void HumanFound::notifySubscribers(Vector3 location) {
  // Notify ICarSubscribers about the found location
  for (auto car : human->getCars()) {
    car->notify(location);
  }
}

void HumanFound::moveTowardsPackage() {
  // Path strategy with JumpDecorator
  IStrategy* pathStrategy = new JumpDecorator(new JumpDecorator(
      new AstarStrategy(human->getPosition(), this->findClosestPackage()->getDestination(),
                        human->getModel()->getGraph())));

  // Increase speed
  human->setSpeed(human->getSpeed() * 2);

  // Travel to package
  pathStrategy->move(human, 1.0);

  // Decrease speed back to original value
  human->setSpeed(human->getSpeed() / 2);

  // Notify ICarSubscribers
  notifySubscribers(this->findClosestPackage()->getDestination());

  // Change state back to Looking
  human->changeState(new HumanLooking(human));
}

Package* HumanFound::findClosestPackage() {
  // Find the closest package among available packages
  std::vector<Package*> packages = human->getPackages();
  Package* closestPackage = nullptr;
  double minDistance = std::numeric_limits<double>::max();

  for (Package* package : packages) {
    double distance = package->getPosition().dist(human->getPosition());
    if (distance < minDistance) {
      minDistance = distance;
      closestPackage = package;
    }
  }

  return closestPackage;
}
