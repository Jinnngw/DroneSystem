/**
 * @file ICelebrationDecorator.cc
 * @brief Implementation of the ICelebrationDecorator class.
 */

#include "ICelebrationDecorator.h"

/**
 * @brief Constructs the ICelebrationDecorator object.
 * @param strategy Strategy to be decorated with celebration.
 * @param time Duration of the celebration.
 */
ICelebrationDecorator::ICelebrationDecorator(IStrategy* strategy, double time) {
  this->strategy = strategy;
  this->time = time;
}

/**
 * @brief Destructor for ICelebrationDecorator.
 */
ICelebrationDecorator::~ICelebrationDecorator() {
  // Delete dynamically allocated variables
  if (strategy) delete strategy;
}

/**
 * @brief Moves the entity according to the strategy and handles the celebration.
 * @param entity Entity to be moved.
 * @param dt Time step for the movement.
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
 * @return True if the celebration time has elapsed, false otherwise.
 */
bool ICelebrationDecorator::isCompleted() {
  return time <= 0;
}

