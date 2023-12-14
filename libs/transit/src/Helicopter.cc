#define _USE_MATH_DEFINES
#include "Helicopter.h"

#include <cmath>
#include <limits>

#include "BeelineStrategy.h"

/**
 * @brief Constructor for Helicopter. Initializes the helicopter with given JSON data.
 * @param obj JSON object containing initialization data for the helicopter.
 */
Helicopter::Helicopter(JsonObject& obj) : IEntity(obj) {}

/**
 * @brief Destructor for Helicopter. Cleans up resources.
 */
Helicopter::~Helicopter() {
  if (movement) delete movement;
}

/**
 * @brief Update function for Helicopter. Manages the movement and behavior of the helicopter.
 * @param dt Time step for the update.
 */
void Helicopter::update(double dt) {
  if (movement && !movement->isCompleted()) {
    movement->move(this, dt);
  } else {
    if (movement) delete movement;
    Vector3 dest;
    dest.x = ((static_cast<double>(rand())) / RAND_MAX) * (2900) - 1400;
    dest.y = position.y;
    dest.z = ((static_cast<double>(rand())) / RAND_MAX) * (1600) - 800;
    movement = new BeelineStrategy(position, dest);
  }
}

/**
 * @brief Subscribes an observer to the helicopter. Currently unimplemented.
 * @param observer Pointer to the IObserver to subscribe.
 */
void Helicopter::subscribe(IObserver* observer) {}

/**
 * @brief Unsubscribes an observer from the helicopter. Currently unimplemented.
 * @param observer Pointer to the IObserver to unsubscribe.
 */
void Helicopter::unsubscribe(IObserver* observer) {}

/**
 * @brief Notifies all subscribers with a specific context. Currently unimplemented.
 * @param context The context of the notification as a string.
 * @return True if successful, otherwise false.
 */
bool Helicopter::notifySubscribers(std::string context) { return true;}