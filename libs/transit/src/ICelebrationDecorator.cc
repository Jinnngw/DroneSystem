#include "ICelebrationDecorator.h"
#include "PathStrategy.h"

ICelebrationDecorator::ICelebrationDecorator(PathStrategy* strategy, double time) {
  this->strategy = strategy;
  this->time = time;
}

ICelebrationDecorator::~ICelebrationDecorator() {
  // Delete dynamically allocated variables
  if (strategy) delete strategy;
}

void ICelebrationDecorator::move(IEntity* entity, double dt) {
  if (!strategy->isCompleted()) {
    strategy->move(entity, dt);
  } else if (!isCompleted()) {
    celebrate(entity, dt);
    time -= dt;
  }
}

bool ICelebrationDecorator::isCompleted() {
  return time <= 0;
}

std::vector<std::vector<float>> ICelebrationDecorator::getPath(){
  return dynamic_cast<PathStrategy*>(strategy)->getPath();
}