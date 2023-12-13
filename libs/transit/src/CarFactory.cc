/**
 * @file CarFactory.cc
 * @brief Implements the factory for creating Car objects.
 */

#include "CarFactory.h"

/**
 * @brief Creates a Car entity.
 * @param entity JSON object containing initialization data.
 * @return Pointer to the created Car entity, or nullptr if creation fails.
 */
IEntity* CarFactory::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("car") == 0) {
    std::cout << "Car Created" << std::endl;
    return new Car(entity);
  }
  return nullptr;
}