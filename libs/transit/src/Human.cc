/**
 * @file Human.cc
 * @brief Implementation of the Human class.
 */

#define _USE_MATH_DEFINES
#include "Human.h"

#include <cmath>
#include <limits>

#include "AstarStrategy.h"
#include "SimulationModel.h"


/**
 * @brief Constructs a Human object.
 * @param obj Initialization data for the Human.
 */
Human::Human(JsonObject& obj) : IEntity(obj) {}

/**
 * @brief Destructor for the Human class, deallocates movement strategy.
 */
Human::~Human() {
  if (movement) delete movement;
}

/**
 * @brief Updates the Human's state.
 * @param dt The time step for updating the human's position and state.
 */
void Human::update(double dt) {
  if (movement && !movement->isCompleted()) {
    movement->move(this, dt);
  } else {
    if (movement) delete movement;
    Vector3 dest;
    dest.x = ((static_cast<double>(rand())) / RAND_MAX) * (2900) - 1400;
    dest.y = position.y;
    dest.z = ((static_cast<double>(rand())) / RAND_MAX) * (1600) - 800;
    if (model)
      movement = new AstarStrategy(position, dest, model->getGraph());
  }
}
