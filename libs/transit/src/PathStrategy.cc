/**
 * @file PathStrategy.cc
 * @brief Implementation of the PathStrategy class.
 */

#include "PathStrategy.h"

/**
 * @brief Constructs the PathStrategy object.
 * @param p Vector of path points.
 */
PathStrategy::PathStrategy(std::vector<std::vector<float>> p)
  : path(p), index(0) {}

/**
 * @brief Moves the entity along the path.
 * @param entity Entity to be moved.
 * @param dt Time step for the movement.
 */
void PathStrategy::move(IEntity* entity, double dt) {
  if (isCompleted())
    return;

  Vector3 vi(path[index][0], path[index][1], path[index][2]);
  Vector3 dir = (vi - entity->getPosition()).unit();

  entity->setPosition(entity->getPosition() + dir*entity->getSpeed()*dt);
  entity->setDirection(dir);

  if (entity->getPosition().dist(vi) < 4)
    index++;
}

/**
 * @brief Checks if the path traversal is completed.
 * @return True if the path is completed, false otherwise.
 */
bool PathStrategy::isCompleted() {
  return index >= path.size();
}
