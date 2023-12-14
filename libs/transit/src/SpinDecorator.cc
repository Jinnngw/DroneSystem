/**
 * @file SpinDecorator.cc
 * @brief Implementation of the SpinDecorator class.
 */

#include "SpinDecorator.h"

/**
 * @brief Constructs the SpinDecorator object.
 * @param strategy Strategy to be decorated with spinning.
 * @param time Duration of the spinning.
 * @param spinSpeed Speed of the spin.
 */
SpinDecorator::SpinDecorator(IStrategy* strategy, double time, double spinSpeed)
  : ICelebrationDecorator(strategy, time), spinSpeed(spinSpeed) {}

/**
 * @brief Executes the celebration (spinning) for the entity.
 * @param entity Entity that performs the celebration.
 * @param dt Time step for the celebration.
 */
void SpinDecorator::celebrate(IEntity* entity, double dt) {
  entity->rotate(dt*entity->getSpeed()*spinSpeed);
}
