#include "Package.h"

#include "Robot.h"

/**
 * @brief Constructor for Package. Initializes the package with given JSON data.
 * @param obj JSON object containing initialization data for the package.
 */
Package::Package(JsonObject &obj) : IEntity(obj) {
}

/**
 * @brief Retrieves the destination of the package.
 * @return The destination as a Vector3 object.
 */
Vector3 Package::getDestination() const {
  return destination;
}

/**
 * @brief Retrieves the strategy name associated with the package.
 * @return The strategy name as a string.
 */
std::string Package::getStrategyName() const {
  return strategyName;
}

/**
 * @brief Sets the strategy name for the package.
 * @param strategyName_ The new strategy name.
 */
void Package::setStrategyName(std::string strategyName_) {
  strategyName = strategyName_;
}

/**
 * @brief Update function for Package. Currently does nothing.
 * @param dt Time step for the update.
 */
void Package::update(double dt) {}

/**
 * @brief Initializes the delivery process with a specified owner (Robot).
 * @param owner Pointer to the Robot that owns this package.
 */
void Package::initDelivery(Robot* owner) {
  this->owner = owner;
  owner->requestedDelivery = false;
  requiresDelivery = false;
  destination = owner->getPosition();
}

/**
 * @brief Hands off the package to its owner.
 */
void Package::handOff() {
  if (owner) {
    owner->receive(this);
  }
}

/**
 * @brief Subscribes an observer to the package. Currently unimplemented.
 * @param observer Pointer to the IObserver to subscribe.
 */
void Package::subscribe(IObserver* observer) {}

/**
 * @brief Unsubscribes an observer from the package. Currently unimplemented.
 * @param observer Pointer to the IObserver to unsubscribe.
 */
void Package::unsubscribe(IObserver* observer) {}

/**
 * @brief Notifies all subscribers with a specific context. Currently unimplemented.
 * @param context The context of the notification as a string.
 * @return True if successful, otherwise false.
 */
bool Package::notifySubscribers(std::string context) { return true;}