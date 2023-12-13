#include "PathStrategy.h"

PathStrategy::PathStrategy(std::vector<std::vector<float>> p)
  : path(p), index(0) {

  }

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

bool PathStrategy::isCompleted() {
  return index >= path.size();
}

std::vector<std::vector<float>> PathStrategy::getPath(){
  return this->path;
}

void PathStrategy::setPath(std::vector<std::vector<float>> path){
  this->path = path;
}

