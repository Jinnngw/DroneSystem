#include "PathStrategy.h"

PathStrategy::PathStrategy(std::vector<std::vector<float>> p)
  : path(p), index(0) {

  }

void PathStrategy::moveAltitude(IEntity* entity, double dt, float altitudeModifier) {
  if (isCompleted())
    return;

  std::cout << path.size() << std::endl;
  std::cout << path[index][1] << std::endl;
  std::cout << altitudeModifier << std::endl;
  std::cout << "here" << std::endl;
  

  Vector3 vi(path[index][0], path[index][1] + altitudeModifier, path[index][2]);

  std::cout << "here2" << std::endl;

  Vector3 dir = (vi - entity->getPosition()).unit();

  std::cout << "here3" << std::endl;

  entity->setPosition(entity->getPosition() + dir*entity->getSpeed()*dt);
  entity->setDirection(dir);

  if (entity->getPosition().dist(vi) < 4)
    index++;
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

