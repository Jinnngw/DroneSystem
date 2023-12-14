/**
 * @file Package.cc
 * @brief Implementation of the Package class.
 */

#include "Package.h"

#include "Robot.h"

/**
 * @brief Constructs a Package object.
 * @param obj Initialization data for the Package.
 */
Package::Package(JsonObject &obj) : IEntity(obj) {
}

/**
 * @brief Gets the destination of the package.
 * @return The destination as a Vector3 object.
 */
Vector3 Package::getDestination() const {
  return destination;
}

/**
 * @brief Gets the strategy name associated with the package.
 * @return The name of the strategy as a string.
 */
std::string Package::getStrategyName() const {
  return strategyName;
}

/**
 * @brief Sets the strategy name for the package.
 * @param strategyName_ The strategy name to set.
 */
void Package::setStrategyName(std::string strategyName_) {
  strategyName = strategyName_;
}

/**
 * @brief Updates the package. This method is typically called every frame.
 * @param dt Time step for the update.
 */
void Package::update(double dt) {}

/**
 * @brief Initializes the delivery process for the package.
 * @param owner The Robot object which will take ownership of the package.
 */
void Package::initDelivery(Robot* owner) {
  this->owner = owner;
  owner->requestedDelivery = false;
  requiresDelivery = false;
  destination = owner->getPosition();
}

/**
 * @brief Hands off the package to its destination.
 */
void Package::handOff() {
  if (owner) {
    owner->receive(this);
  }
}
