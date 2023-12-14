#include "ICelebrationDecorator.h"
#include "PathStrategy.h"

/**
 * @brief Constructor for ICelebrationDecorator.
 * @param strategy Pointer to the PathStrategy being decorated.
 * @param time Duration for the celebration.
 */
ICelebrationDecorator::ICelebrationDecorator(PathStrategy* strategy, double time) {
  this->strategy = strategy;
  this->time = time;
}

/**
 * @brief Destructor for ICelebrationDecorator. Cleans up resources.
 */
ICelebrationDecorator::~ICelebrationDecorator() {
  // Delete dynamically allocated variables
  if (strategy) delete strategy;
}

/**
 * @brief Moves the entity according to the decorated strategy and celebration logic.
 * @param entity Pointer to the IEntity being moved.
 * @param dt Time step for the update.
 */
void ICelebrationDecorator::move(IEntity* entity, double dt) {
  if (!strategy->isCompleted()) {
    strategy->move(entity, dt);
  } else if (!isCompleted()) {
    celebrate(entity, dt);
    time -= dt;
  }
}

/**
 * @brief Checks if the celebration is completed.
 * @return True if celebration is completed, false otherwise.
 */
bool ICelebrationDecorator::isCompleted() {
  return time <= 0;
}

/**
 * @brief Retrieves the path followed by the decorated strategy.
 * @return A vector of vectors of floats representing the path.
 */
std::vector<std::vector<float>> ICelebrationDecorator::getPath(){
  return dynamic_cast<PathStrategy*>(strategy)->getPath();
}