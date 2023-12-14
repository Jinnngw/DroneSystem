#include "Robot.h"

/**
 * @brief Constructor for Robot. Initializes the robot with given JSON data.
 * @param obj JSON object containing initialization data for the robot.
 */
Robot::Robot(JsonObject &obj) : IEntity(obj) {}

/**
 * @brief Update function for Robot. Currently does nothing.
 * @param dt Time step for the update.
 */
void Robot::update(double dt) {}

/**
 * @brief Receives a package.
 * @param p Pointer to the Package received.
 */
void Robot::receive(Package* p) {
  package = p;
}

/**
 * @brief Subscribes an observer to the robot. Currently unimplemented.
 * @param observer Pointer to the IObserver to subscribe.
 */
void Robot::subscribe(IObserver* observer) {}

/**
 * @brief Unsubscribes an observer from the robot. Currently unimplemented.
 * @param observer Pointer to the IObserver to unsubscribe.
 */
void Robot::unsubscribe(IObserver* observer) {}

/**
 * @brief Notifies all subscribers with a specific context. Currently unimplemented.
 * @param context The context of the notification as a string.
 * @return True if notification is sent successfully, false otherwise.
 */
bool Robot::notifySubscribers(std::string context) { return true;}