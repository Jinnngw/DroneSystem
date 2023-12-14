/**
 * @file IEntity.cc
 * @brief Implementation of the IEntity class.
 */

#include "IEntity.h"

/**
 * @brief Default constructor for IEntity.
 */
IEntity::IEntity() {
  static int currentId = 0;
  id = currentId;
  currentId++;
}

/**
 * @brief Constructs IEntity with details.
 * @param details JSON object containing entity details.
 */
IEntity::IEntity(JsonObject& details) : IEntity() {
  this->details = details;
  JsonArray pos(details["position"]);
  position = {pos[0], pos[1], pos[2]};
  JsonArray dir(details["direction"]);
  direction = {dir[0], dir[1], dir[2]};
  if (details.contains("color")) {
    std::string col = details["color"];
    color = col;
  }
  std::string n = details["name"];
  name = n;
  speed = details["speed"];
}

/**
 * @brief Destructor for IEntity.
 */
IEntity::~IEntity() {}

/**
 * @brief Links the entity with a simulation model.
 * @param model Pointer to the simulation model.
 */
void IEntity::linkModel(SimulationModel* model) {
  this->model = model;
}

/**
 * @brief Retrieves the entity's ID.
 * @return Entity ID.
 */
int IEntity::getId() const {
  return id;
}

/**
 * @brief Retrieves the entity's position.
 * @return Entity position.
 */
Vector3 IEntity::getPosition() const {
  return position;
}

/**
 * @brief Retrieves the entity's direction.
 * @return Entity direction.
 */
Vector3 IEntity::getDirection() const {
  return direction;
}

/**
 * @brief Retrieves details of the entity.
 * @return Entity details as a JSON object.
 */
const JsonObject& IEntity::getDetails() const {
  return details;
}

/**
 * @brief Retrieves the entity's color.
 * @return Entity color.
 */
std::string IEntity::getColor() const {
  return color;
}

/**
 * @brief Retrieves the entity's name.
 * @return Entity name.
 */
std::string IEntity::getName() const {
  return name;
}

/**
 * @brief Retrieves the entity's speed.
 * @return Entity speed.
 */
double IEntity::getSpeed() const {
  return speed;
}

/**
 * @brief Sets the entity's position.
 * @param pos_ New position for the entity.
 */
void IEntity::setPosition(Vector3 pos_) {
  position = pos_;
}

/**
 * @brief Sets the entity's direction.
 * @param dir_ New direction for the entity.
 */
void IEntity::setDirection(Vector3 dir_) {
  direction = dir_;
}

/**
 * @brief Sets the entity's color.
 * @param col_ New color for the entity.
 */
void IEntity::setColor(std::string col_) {
  color = col_;
}

/**
 * @brief Rotates the entity by a given angle.
 * @param angle Angle in radians to rotate the entity.
 */
void IEntity::rotate(double angle) {
  Vector3 dirTmp = direction;
  direction.x = dirTmp.x * std::cos(angle) - dirTmp.z * std::sin(angle);
  direction.z = dirTmp.x * std::sin(angle) + dirTmp.z * std::cos(angle);
}
