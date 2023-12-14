#include "SpinDecorator.h"

/**
 * @brief Constructor for SpinDecorator.
 * @param strategy Pointer to the PathStrategy being decorated.
 * @param time Duration for the spin decoration.
 * @param spinSpeed Speed of the spin.
 */
SpinDecorator::SpinDecorator(PathStrategy* strategy, double time, double spinSpeed)
  : ICelebrationDecorator(strategy, time), spinSpeed(spinSpeed) {}

/**
 * @brief Celebration logic for the spin decorator.
 * @param entity Pointer to the IEntity being decorated.
 * @param dt Time step for the update.
 */
void SpinDecorator::celebrate(IEntity* entity, double dt) {
  entity->rotate(dt*entity->getSpeed()*spinSpeed);
}
