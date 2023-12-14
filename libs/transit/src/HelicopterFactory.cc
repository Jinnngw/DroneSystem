/**
 * @file HelicopterFactory.cc
 * @brief Implementation of the Factory pattern for creating Helicopter objects.
 */

#include "HelicopterFactory.h"

/**
 * @brief Creates a Helicopter entity based on a given type.
 * @param entity Entity details in JsonObject form.
 * @return Pointer to created Helicopter object, or nullptr if type does not match.
 */
IEntity* HelicopterFactory::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("helicopter") == 0) {
    std::cout << "Helicopter Created" << std::endl;
    return new Helicopter(entity);
  }
  return nullptr;
}
