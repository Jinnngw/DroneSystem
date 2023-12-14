#include "PathStrategy.h"

/**
 * @brief Constructor for PathStrategy. Initializes a path-following strategy.
 * @param p Vector of vectors of floats representing the path coordinates.
 */
PathStrategy::PathStrategy(std::vector<std::vector<float>> p)
  : path(p), index(0) {

  }

/**
 * @brief Moves an entity along the predefined path.
 * @param entity Pointer to the IEntity being moved.
 * @param dt Time step for the update.
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
 * @brief Checks if the path-following is completed.
 * @return True if path-following is completed, false otherwise.
 */
bool PathStrategy::isCompleted() {
  return index >= path.size();
}

/**
 * @brief Retrieves the path.
 * @return A vector of vectors of floats representing the path.
 */
std::vector<std::vector<float>> PathStrategy::getPath(){
  return this->path;
}

/**
 * @brief Sets the path for the strategy.
 * @param path Vector of vectors of floats representing the new path.
 */
void PathStrategy::setPath(std::vector<std::vector<float>> path){
  this->path = path;
}

