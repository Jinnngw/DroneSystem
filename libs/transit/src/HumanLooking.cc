#include "HumanLooking.h"

#include "AstarStrategy.h"

void HumanLooking::update(double dt) {
  if (human->getMovement() && !human->getMovement()->isCompleted()) {
    human->getMovement()->move(human, dt);
  } else {
    if (human->getMovement()) human->deleteMovement();
    Vector3 dest;
    dest.x = ((static_cast<double>(rand())) / RAND_MAX) * (2900) - 1400;
    dest.y = human->getPosition().y;
    dest.z = ((static_cast<double>(rand())) / RAND_MAX) * (1600) - 800;
    if (human->getModel())
      human->setMovement(new AstarStrategy(human->getPosition(), dest,
                                           human->getModel()->getGraph()));
  }

  for (auto package : packages) {
    double distance = (package->getPosition() - human->getPosition()).length();
    // Assuming 100 units is the detection radius
    if (distance < 100.0) {
      // A package is close by, change state to Found
      human->changeState(new HumanFound());
      return;
    }
  }
}
