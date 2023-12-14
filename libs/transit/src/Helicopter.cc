/**
 * @file Helicopter.cc
 * @brief Implementation of the Helicopter class.
 */

#define _USE_MATH_DEFINES
#include "Helicopter.h"

#include <cmath>
#include <limits>

#include "BeelineStrategy.h"

/**
 * @brief Constructs a Helicopter object.
 * @param obj Initialization data for the Helicopter.
 */
Helicopter::Helicopter(JsonObject& obj) : IEntity(obj) {}

/**
 * @brief Destructor for the Helicopter class, deallocates movement strategy.
 */
Helicopter::~Helicopter() {
  if (movement) delete movement;
}

/**
 * @brief Updates the Helicopter's state.
 * @param dt The time step for updating the helicopter's position and state.
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
