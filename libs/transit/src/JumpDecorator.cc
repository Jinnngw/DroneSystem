/**
 * @file JumpDecorator.cc
 * @brief Implementation of the JumpDecorator class.
 */

#include "JumpDecorator.h"

/**
 * @brief Constructs the JumpDecorator object.
 * @param strategy Strategy to be decorated with jumping.
 * @param time Duration of the jumping.
 * @param jumpHeight Height of the jump.
 */
JumpDecorator::JumpDecorator(IStrategy* strategy, double time,
  double jumpHeight)
  : ICelebrationDecorator(strategy, time), jumpHeight(jumpHeight) {}

/**
 * @brief Executes the celebration (jumping) for the entity.
 * @param entity Entity that performs the celebration.
 * @param dt Time step for the celebration.
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
