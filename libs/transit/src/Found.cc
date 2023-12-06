#include "Found.h"

#include "AstarStrategy.h"
#include "JumpDecorator.h"

void Found::update(double dt) {
  Package* closestPackage = findClosestPackage();

  if (closestPackage) {
    moveTowardsPackage();
  } else {
    // No package found, revert to Looking state
    human->changeState(new Looking(human));
  }
}

void Found::notifySubscribers(Vector3 location) {
  // Notify ICarSubscribers about the found location
  for (auto car : human->getCars()) {
    car->notify(location);
  }
}

void Found::moveTowardsPackage() {
  // Path strategy with JumpDecorator
  IStrategy* pathStrategy = new JumpDecorator(new JumpDecorator(
      new AstarStrategy(human->getPosition(), closestPackage->getDestination(),
                        model->getGraph())));

  // Increase speed
  double originalSpeed = human->speed;
  human->speed *= 2.0;

  // Travel to package
  pathStrategy->move(human, 1.0);

  // Decrease speed back to original value
  human->speed = originalSpeed;

  // Notify ICarSubscribers
  notifySubscribers(closestPackage->getDestination());

  // Change state back to Looking
  human->changeState(new Looking(human));
}

Package* Found::findClosestPackage() {
  // Find the closest package among available packages
  std::vector<Package*> packages = human->getPackages();
  Package* closestPackage = nullptr;
  double minDistance = std::numeric_limits<double>::max();

  for (auto package : packages) {
    double distance = (package->getPosition() - human->getPosition()).length();
    if (distance < minDistance) {
      minDistance = distance;
      closestPackage = package;
    }
  }

  return closestPackage;
}
