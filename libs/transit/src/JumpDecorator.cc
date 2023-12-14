#include "JumpDecorator.h"

/**
 * @brief Constructor for JumpDecorator.
 * @param strategy Pointer to the PathStrategy being decorated.
 * @param time Duration for the jump decoration.
 * @param jumpHeight Height of the jump.
 */
JumpDecorator::JumpDecorator(PathStrategy* strategy, double time,
  double jumpHeight)
  : ICelebrationDecorator(strategy, time), jumpHeight(jumpHeight) {}

/**
 * @brief Celebration logic for the jump decorator.
 * @param entity Pointer to the IEntity being decorated.
 * @param dt Time step for the update.
 */
void JumpDecorator::celebrate(IEntity* entity, double dt) {
  Vector3 step(0, entity->getSpeed() * dt, 0);
  if (up) {
    h += step.y;
    entity->setPosition(entity->getPosition() + step);
    if (h >= jumpHeight) up = false;
  } else {
    h -= step.y;
    entity->setPosition(entity->getPosition() - step);
    if (h <= 0) up = true;
  }
}
