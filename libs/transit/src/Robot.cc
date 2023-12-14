/**
 * @file Robot.cc
 * @brief Implementation of the Robot class.
 */

#include "Robot.h"

/**
 * @brief Constructs a Robot object.
 * @param obj Initialization data for the Robot.
 */
Robot::Robot(JsonObject &obj) : IEntity(obj) {}

/**
 * @brief Updates the Robot's state.
 * @param dt The time step for updating the robot's position and state.
 */
void Robot::update(double dt) {}

/**
 * @brief Receives a package to be delivered by the robot.
 * @param p Pointer to the package to be received.
 */
void Robot::receive(Package* p) {
  package = p;
}
