#include "Looking.h"

#include "AstarStrategy.h"

void Looking::update(double dt) {
  if (human->movement && !human->movement->isCompleted()) {
    human->movement->move(human, dt);
  } else {
    if (human->movement) delete human->movement;
    Vector3 dest;
    dest.x = ((static_cast<double>(rand())) / RAND_MAX) * (2900) - 1400;
    dest.y = human->getPosition().y;
    dest.z = ((static_cast<double>(rand())) / RAND_MAX) * (1600) - 800;
    if (human->getModel())
      human->movement = new AstarStrategy(human->getPosition(), dest,
                                          human->getModel()->getGraph());
  }

  for (auto package : packages) {
    double distance = (package->getPosition() - human->getPosition()).length();
    // Assuming 100 units is the detection radius
    if (distance < 100.0) {
      // A package is close by, change state to Found
      human->changeState(new Found(human));
      return;
    }
  }
}
