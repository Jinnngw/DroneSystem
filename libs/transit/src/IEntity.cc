#include "IEntity.h"

/**
 * @brief Default constructor for IEntity. Initializes an entity with a unique ID.
 */
IEntity::IEntity() {
  static int currentId = 0;
  id = currentId;
  currentId++;
}

/**
 * @brief Constructor for IEntity. Initializes an entity with details from a JSON object.
 * @param details JSON object containing initialization data for the entity.
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
 * @brief Links this entity to a simulation model.
 * @param model Pointer to the SimulationModel.
 */
void IEntity::linkModel(SimulationModel* model) {
  this->model = model;
}

/**
 * @brief Retrieves the unique ID of the entity.
 * @return The unique ID of the entity.
 */
int IEntity::getId() const {
  return id;
}

/**
 * @brief Retrieves the current position of the entity.
 * @return The position as a Vector3 object.
 */
Vector3 IEntity::getPosition() const {
  return position;
}

/**
 * @brief Retrieves the current direction of the entity.
 * @return The direction as a Vector3 object.
 */
Vector3 IEntity::getDirection() const {
  return direction;
}

/**
 * @brief Retrieves the details of the entity in a JSON object format.
 * @return The details as a const reference to a JsonObject.
 */
const JsonObject& IEntity::getDetails() const {
  return details;
}

/**
 * @brief Retrieves the color of the entity.
 * @return The color as a string.
 */
std::string IEntity::getColor() const {
  return color;
}

/**
 * @brief Retrieves the name of the entity.
 * @return The name as a string.
 */
std::string IEntity::getName() const {
  return name;
}

/**
 * @brief Retrieves the speed of the entity.
 * @return The speed as a double.
 */
double IEntity::getSpeed() const {
  return speed;
}

/**
 * @brief Sets the speed of the entity.
 * @param speed New speed value.
 */
void IEntity::setSpeed(double speed) {
  this->speed = speed;
}

/**
 * @brief Retrieves the associated simulation model of the entity.
 * @return Pointer to the SimulationModel.
 */
SimulationModel* IEntity::getModel() const {
  return model;
}

/**
 * @brief Sets the position of the entity.
 * @param pos_ New position for the entity.
 */
void IEntity::setPosition(Vector3 pos_) {
  position = pos_;
}

/**
 * @brief Sets the direction of the entity.
 * @param dir_ New direction for the entity.
 */
void IEntity::setDirection(Vector3 dir_) {
  direction = dir_;
}

/**
 * @brief Sets the color of the entity.
 * @param col_ New color for the entity.
 */
void IEntity::setColor(std::string col_) {
  color = col_;
}

/**
 * @brief Sets a detail key-value pair for the entity.
 * @param key The detail key.
 * @param value The detail value.
 */
void IEntity::setDetails(std::string key, std::string value){
  details[key] = value;
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
